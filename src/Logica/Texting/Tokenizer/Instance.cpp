#include "Logica/Texting/Tokenizer/Instance.hpp"
#include <iostream>

// NOTE: pull any character:
inline Logica::Types::Basic::String Logica::Texting::Tokenizer::Instance::__GetDelimitedToken(
    const Logica::Types::Basic::I32 starter
)
{
    Logica::Types::Basic::String accumulator;
    accumulator.push_back((Logica::Types::Basic::CH8)(starter));
    for(;;)
    {
        Logica::Types::Basic::I32 current_character = this->__GetCharacter();
        if(this->rules->is_token_delimiter(current_character))
            break;
        else if(this->rules->is_token_highlight(current_character))
        {
            /* NOTE: in this case, do something more important:
             * 1-) Due the rules and the linearity of the tokenizer, we put the position on the
             * buffer to before this token, basically we __RewindBuffer() here to avoid losing the
             * next token. On the next token, it is GUARANTEED for this->rules->is_token_highlight
             * to be trigged, unless the character is a token delimiter, which in this case, will
             * create an feed back, for example, if the '\n' is a token delimiter and also a high
             * light token, then we MIGHT have a problem that '\n' will be called to here, the
             * starter token will be: ['\n', ... whatever comes next until break of this loop].
             * 
             * XXX: on the future, give an better look into this?
             */
            this->__RewindBuffer(1);
            break;
        }
        else if(current_character == EOF)
        {
            /* TODO: personalize whether the EOF is considered. */
            break;
        }
        else
            accumulator.push_back((Logica::Types::Basic::CH8)(current_character));
    }
    return accumulator;
}

/* TODO: literal interpretation: */
inline Logica::Types::Basic::CH8 Logica::Texting::Tokenizer::Instance::__GetEscapeCharacter(

)
{
    Logica::Types::Basic::CH8 result = 0;
    Logica::Types::Basic::I32 initial_character = this->__GetCharacter();
    /* NOW for quick returns:
     * \n -> new line
     * \r -> carriage return
     * \" -> for literal "
     * \' -> for literal '
     * \\ -> for literal \
     * \t -> for horizontal tab
     */
    switch(initial_character)
    {
        case 'n':
            result = '\n';
            goto non_numbers;
        case 'r':
            result = '\r';
            goto non_numbers;
        case 't':
            result = '\r';
            goto non_numbers;
        case '"':
            result = '"';
            goto non_numbers;
        case '\'':
            result = '\'';
            goto non_numbers;
        case '\\':
            result = '\\';
            goto non_numbers;
        default:
            break;
    };
    
    /* TODO: do string literals that are: \{numbers} */
    std::abort();

    /* non-numbers literals: */
    non_numbers:
    return result;
}

inline Logica::Types::Basic::String Logica::Texting::Tokenizer::Instance::__GetDelimitedString(
    const Logica::Types::Basic::I32 starter
)
{
    Logica::Types::Basic::String accumulator;
    accumulator.push_back((Logica::Types::Basic::CH8)(starter));
    for(;;)
    {
        Logica::Types::Basic::I32 current_character = this->__GetCharacter();
        if(current_character == starter)
        {
            accumulator.push_back((Logica::Types::Basic::CH8)(current_character));
            break;
        }
        else if(current_character == EOF)
        {
            /* TODO: set the policy for unbroken strings! */
            this->validator.SetError(
                Logica::Texting::Tokenizer::InstanceErrorCodes::BadString,
                "Early End of string on line %d",
                this->line_counter
            );
            this->state = Logica::Texting::Tokenizer::InstanceStatus::Died;
            break;
        }
        else if(current_character == '\\')
            accumulator.push_back(this->__GetEscapeCharacter());
        else
            accumulator.push_back((Logica::Types::Basic::CH8)(current_character));
    }
    return accumulator;
}

/* NOTE: this is an refactoring of the __DetermineCommentTypeAndWasteComment for the following
 * options, all inline functions, to an inline function.
 */
inline void Logica::Texting::Tokenizer::Instance::__ProceedLineCommentUsingRuleSingleLineCommentHint(
    const Logica::Types::Basic::I32 comment_type_hint
)
{
    /* for when the '//' is true: */
    if(comment_type_hint == this->rules->comment_single_line_hint)
        this->__WasteLineComment();
    else
    {
        this->state = Logica::Texting::Tokenizer::InstanceStatus::Died;
        this->validator.SetError(
            Logica::Texting::Tokenizer::InstanceErrorCodes::BadComment,
            "Near line %d, there is a bad comment formed, expected %c, got = %c",
            this->line_counter,
            (char)this->rules->comment_single_line_hint,
            (char)comment_type_hint
        );
    }
}

/* This function only exists for determine the type of line comment, there are a few options: 
 * '//'       -> in this case, there is in the rules (comment_single_line_hint) the '/' key
 * '#'        -> in this case, the (comment_single_hint_hint) rule is 0.
 * In both of the cases, the simplest is the second one as we just need to account for '\n'
 * to break the line.
 */
inline void Logica::Texting::Tokenizer::Instance::__DetermineLineCommentTypeAndWasteComment(
    const Logica::Types::Basic::I32 comment_type_hint
)
{
    if(this->rules->comment_single_line_hint == 0)
    {
        /* for when the '#' only: */
        if(comment_type_hint != '\n')
            this->__WasteLineComment();
    }
    else
        this->__ProceedLineCommentUsingRuleSingleLineCommentHint(comment_type_hint);
}

inline void Logica::Texting::Tokenizer::Instance::__DetermineCommentTypeAndWasteComment(
    const Logica::Types::Basic::I32 comment_type_hint
)
{
    /* NOTE: determine whether we are doing an line comment or delimited comment: */
    if(comment_type_hint == this->rules->comment_delimited_hint)
        this->__WasteDelimitedComment();
    else
        this->__DetermineLineCommentTypeAndWasteComment(comment_type_hint);
}

inline void Logica::Texting::Tokenizer::Instance::__WasteLineComment()
{
    /* Wait to the line to reach new line: */
    /* NOTE: there are some cases to consider:
     * 1-) '\n' for lines that break early.
     * ^ BUT IN THIS CASE, THIS IS DONE ON GET_TOKEN()
     * 2-) ... until the line.
     */
    for(;;)
    {
        Logica::Types::Basic::I32 current_character = this->__GetCharacter();
        if(
            (
                current_character == '\n' ||
                current_character == EOF
            )
        )
            break;
        else
            continue;
    }
}

inline void Logica::Texting::Tokenizer::Instance::__WasteDelimitedComment()
{
    Logica::Types::Basic::Boolean altered = false;
    const Logica::Types::Basic::U32 operation_linestamp = this->line_counter;
    
    for(;;)
    {
        Logica::Types::Basic::I32 current_character = this->__GetCharacter();

        /* FOR both of the options, either altered or not, the EOF is the end. */
        if(current_character == EOF)
        {
            this->state = Logica::Texting::Tokenizer::InstanceStatus::Died;
            this->validator.SetError(
                Logica::Texting::Tokenizer::InstanceErrorCodes::EarlyEndOfLine,
                "Invalid delimited comment started on line %d",
                operation_linestamp
            );
            break;
        }
        /* WHEN altered = false, it means we didn't find the '*' yet.
         * WHEN altered = true, it means we DID find the '*' and we are waiting for the starter
         * again.
         */
        if(altered)
        {
            if((current_character == this->rules->comment_starter))
                break;
            altered = false;
        }
        else
        {
            if((current_character == this->rules->comment_delimited_hint))
                altered = true;
            continue;
        }
    }
}

inline void Logica::Texting::Tokenizer::Instance::__TreatEOF(
    Logica::Types::Basic::Boolean consider_eof
)
{
    if(consider_eof)
    {
        /* THEN EOF is good, just set the machine to finish. */
        this->state = Logica::Texting::Tokenizer::InstanceStatus::Finished;
    }
    else
    {
        this->state = Logica::Texting::Tokenizer::InstanceStatus::Died;
        this->validator.SetError(
            Logica::Texting::Tokenizer::InstanceErrorCodes::BadString,
            "Bad String at line %d",
            this->line_counter
        );
    }
}

inline void Logica::Texting::Tokenizer::Instance::__RewindBuffer(
    const Logica::Types::Basic::U8 amount
)
{
    const Logica::Types::Basic::Size current_position = this->buffer->GetPosition();
    std::cout
        << __PRETTY_FUNCTION__
        << ": rewind from = "
        << current_position
        << " -> "
        << current_position - amount
        << "\n";
    this->buffer->SetPosition(current_position - amount);
}

/* TODO: this still not perfect for most of the languages to parse! */
inline Logica::Types::Basic::I32 Logica::Texting::Tokenizer::Instance::__GetCharacter()
{
    Logica::Types::Basic::I32 value = this->buffer->GetCharacter();
    if(this->buffer->GetPosition() > this->max_position_ever)
    {
        if(value == '\n')
            this->line_counter++;
        this->max_position_ever = this->buffer->GetPosition();
    }
    return value;
}

Logica::Texting::Tokenizer::Instance::Instance()
{
    /* Set the pointers to NULL: */
    this->buffer = nullptr;
    this->rules = nullptr;

    /* set the counters: */
    this->max_position_ever = 0;
    this->line_counter = 1;
    this->state = 0;
}

Logica::Types::Basic::U32 Logica::Texting::Tokenizer::Instance::GetCurrentLine()
{
    return this->line_counter;
}

void Logica::Texting::Tokenizer::Instance::SetRules(
    Logica::Texting::Tokenizer::Rules* rules
)
{
    this->rules = rules;
}

void Logica::Texting::Tokenizer::Instance::SetBuffer(
    Logica::Types::Stream::Buffer* buffer
)
{
    this->buffer = buffer;
}

Logica::Types::Basic::U8 Logica::Texting::Tokenizer::Instance::GetState()
{
    return this->state;
}

Logica::Types::Basic::String Logica::Texting::Tokenizer::Instance::GetToken(
    Logica::Types::Basic::Boolean consider_eof
)
{
    Logica::Types::Basic::String current_token;
    Logica::Types::Basic::I32 current_character;
    Logica::Types::Basic::I32 comment_type_hint;
top:
    /* NOTE: check if we are running! */
    if(this->state != Logica::Texting::Tokenizer::InstanceStatus::Running)
        goto post_tokenization;
    
    current_character = this->__GetCharacter();
    if(current_character == EOF)
    {
        this->__TreatEOF(consider_eof);
        goto post_tokenization;
    }

    /* 
     * Tokenization by Logica is, accordingly to the rules:
     * 1-) Waste until the token delimiter is over;
     * 2-) Enter string mode if an string token is found;
     * 3-) Highlight specific tokens;
     * 4-) Enter comment mode;
     * 5-) Or just default token.
     */

    if(this->rules->is_token_delimiter(current_character))
    {
        /* NOTE: for token delimitators, just wait for the next token */
        goto top;
    }
    else if(this->rules->is_token_string_delimiter(current_character))
    {
        current_token = this->__GetDelimitedString(current_character);
    }
    else if(this->rules->is_token_highlight(current_character))
    {
        /* NOTE: on that case, the high light token is important enough for have a character
         * just for it. */

        /* NOTE: due some languages having '//' as two types of important characters, either for
         * for '/' as the division operator but also as the '//' comment, to some extra parsing
         * here.
         */
        const Logica::Types::Basic::I32 next_token = this->__GetCharacter();
        if(
            (
                current_character   == this->rules->comment_starter &&
                next_token          == this->rules->comment_single_line_hint
            ) ||
            (
                current_character   == this->rules->comment_starter &&
                next_token          == this->rules->comment_delimited_hint
            )
        )
        {
            /* Set this and move to the comment (leaving this condition block to another). */
            comment_type_hint = next_token;
            goto comment;
        }
        else
        {
            /* HACK: pre check for EOF. */
            if(next_token != EOF)
                this->__RewindBuffer(1);
            current_token.push_back((Logica::Types::Basic::CH8)(current_character));
        }
    }
    else if(current_character == this->rules->comment_starter)
    {
        /* This function can come from the condition is_token_highlight! */
        comment_type_hint = this->__GetCharacter();
        comment:
        this->__DetermineCommentTypeAndWasteComment(comment_type_hint);
        /* NOTE: even if the code is failed, we can safely go back. */
        goto top;
    }
    else
    {
        /* NOTE: in this case, we have an token, considering it isn't any of the other
         * options on the top: */
        current_token = this->__GetDelimitedToken(current_character);
    }
post_tokenization:
    return current_token;
}