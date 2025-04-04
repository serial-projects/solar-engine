#include "Logica/Texting/Tokenizer/Instance.hpp"
#include "Logica/Texting/Tokenizer/Instance.hpp"
#include <iostream>

/*
 * Private:
 */

void Logica::Texting::Tokenizer::Instance::Rewind(
    const Logica::Types::Basic::U8 amount
)
{
    Logica::Types::Basic::Size buffer_current_position = this->working_buffer->GetPosition();
    this->working_buffer->SetPosition(buffer_current_position - amount);
}

Logica::Types::Basic::I32 Logica::Texting::Tokenizer::Instance::GetCharacter()
{
    Logica::Types::Basic::I32   adquired_character      = this->working_buffer->ReadI32();
    Logica::Types::Basic::Size  adquired_at_posiiton    = this->working_buffer->GetPosition() - 1;

    /* Here we ONLY increment when the newline_max_position is passed by the adquired_at_position,
     * in case it isn't then we DON'T increment on the line counter. */
    if(adquired_character == '\n')
    {
        if(adquired_at_posiiton > this->newline_max_position)
        {
            this->line_counter++;
            this->newline_max_position = adquired_at_posiiton;
        }
    }

    return adquired_character;
}

/* TODO: implement octal formats, and more: */

void Logica::Texting::Tokenizer::Instance::GetTokenStringLiteral(
    Logica::Types::Basic::String* key
)
{
    Logica::Types::Basic::I32 literal_character = this->GetCharacter();
    switch(literal_character)
    {
        case (static_cast<Logica::Types::Basic::I32>('n')):             key->push_back('\n'); break;
        case (static_cast<Logica::Types::Basic::I32>('t')):             key->push_back('\t'); break;
        default: key->push_back(static_cast<char>(literal_character)); break;
    }
}

void Logica::Texting::Tokenizer::Instance::GetTokenString(
    Logica::Types::Basic::String* key,
    const Logica::Types::Basic::I32 entrypoint_token
)
{
    Logica::Types::Basic::U32       line_string_started = this->line_counter;
    key->push_back(entrypoint_token);
    for(;;)
    {
        Logica::Types::Basic::I32 current_character = this->GetCharacter();
        if(current_character == EOF)
        {
            this->validator.ReportError(
                Logica::Texting::Tokenizer::Instance::Errors::PREMATURE_STRING_END,
                "Premature end on string that started %d, expected closure on line %d!",
                line_string_started,
                this->line_counter
            );
            this->state = Logica::Texting::Tokenizer::Instance::States::DIED;
            break;
        }
        if(current_character == entrypoint_token)
            break;
        else if(current_character == '\\')
            this->GetTokenStringLiteral(key);
        else
            key->push_back(current_character);
    }
    key->push_back(entrypoint_token);
}

void Logica::Texting::Tokenizer::Instance::GetTokenAny(
    Logica::Types::Basic::String* key,
    const Logica::Types::Basic::I32 entrypoint_token
)
{
    key->push_back(entrypoint_token);
    for(;;)
    {
        Logica::Types::Basic::I32 current_character     = this->GetCharacter();
        Logica::Types::Basic::U8 current_character_type =
            this->current_rules->get_character_type(current_character);
        
        if(current_character == EOF)
        {
            /* Since EOF is not BAD for the token here, we can safely end the token here. */
            break;
        }

        /* keep going: */
        if(
            current_character_type ==
                Logica::Texting::Tokenizer::RulesCharacterType::TokenDelimiter
        )
        {
            break;
        }
        else if(
            current_character_type  ==
                Logica::Texting::Tokenizer::RulesCharacterType::HighlightToken  ||
            current_character_type  ==
                Logica::Texting::Tokenizer::RulesCharacterType::StringDelimiter ||
            /* NOTE: we also consider the current_character to be a comment starter, in case
             * it is, we MUST also back on track to leave for the next GetToken() to process
             * this token.
             */
            current_character       ==
                this->current_rules->comment_token
        )
        {
            this->Rewind(1);
            break;
        }
        else
        {
            key->push_back(static_cast<char>(current_character));
        }
    }
}

void Logica::Texting::Tokenizer::Instance::WasteDelimitedComment()
{
    for(;;)
    {
        Logica::Types::Basic::I32 current_character = this->GetCharacter();
        if(current_character == EOF)
        {
            this->validator.ReportError(
                Logica::Texting::Tokenizer::Instance::Errors::PREMATURE_STRING_END,
                "In line %d, got an incomplete delimited comment",
                this->line_counter
            );
            this->state = Logica::Texting::Tokenizer::Instance::States::DIED;
            break;
        }
        else if(current_character == this->current_rules->delimited_comment_closure_token)
        {
            /* NOTE: if there is a EOF, the next iteration will capture it: */
            Logica::Types::Basic::I32 next_character = this->GetCharacter();
            if(next_character == this->current_rules->comment_token)
                break;
        }
    }
}

void Logica::Texting::Tokenizer::Instance::WasteLineComment()
{
    for(;;)
    {
        Logica::Types::Basic::I32 current_character = this->GetCharacter();
        if(current_character == '\n' || current_character == EOF)
            break;
    }
}

void Logica::Texting::Tokenizer::Instance::WasteComment(
    Logica::Types::Basic::I32 hint
)
{
    if(this->current_rules->delimited_comment_hint_token)
    {
        if(this->current_rules->delimited_comment_hint_token == hint)
        {
            this->WasteDelimitedComment();
            goto past_everything;
        }
    }
    if(this->current_rules->line_comment_hint_token)
    {
        if(this->current_rules->line_comment_hint_token == hint)
            this->WasteDelimitedComment();
        else
        {
            /* BAD TOKEN: */
            this->validator.ReportError(
                Logica::Texting::Tokenizer::Instance::Errors::PREMATURE_STRING_END,
                "Expected %c or %c in line %d for comment, got %c",
                static_cast<char>(this->current_rules->delimited_comment_hint_token),
                static_cast<char>(this->current_rules->line_comment_hint_token), 
                this->line_counter,
                static_cast<char>(hint)
            );
            this->state = Logica::Texting::Tokenizer::Instance::States::DIED;
        }
    }
    else
    {
        if(hint != '\n')
        {
            /* NOTE: we can skip this here since an empty comment can be possible
             * we CAN't return on the time here! */
            this->WasteLineComment();
        }
    }
past_everything:
    return;
}

/*
 * Public:
 */

void Logica::Texting::Tokenizer::Instance::GetToken(
    Logica::Types::Basic::String* key
)
{
    Logica::Types::Basic::I32 current_character         = 0;
    Logica::Types::Basic::U8  current_character_type    = 0;
    Logica::Types::Basic::I32 next_character            = 0;
    key->clear();
top:
    /* Early Checking: */
    if(this->state != Logica::Texting::Tokenizer::Instance::States::RUNNING)
        goto skip_everything;

    current_character       = this->GetCharacter();
    current_character_type  = this->current_rules->get_character_type(current_character);

    if(current_character == EOF)
    {
        this->state = Logica::Texting::Tokenizer::Instance::States::FINISHED;
        goto skip_everything;
    }

    /* The actual parsing here: */

    if (
        current_character_type ==
            Logica::Texting::Tokenizer::RulesCharacterType::TokenDelimiter
    )
    {
        goto top;
    }
    else if(
        current_character_type ==
            Logica::Texting::Tokenizer::RulesCharacterType::StringDelimiter
    )
    {
        this->GetTokenString(key, current_character);
    }
    else if(
        current_character_type ==
            Logica::Texting::Tokenizer::RulesCharacterType::HighlightToken
    )
    {
        /* NOTE: due some languages using '/' for keywords and some other special tokens,
         * like, C has '/' for the division operator and / + * for the comment token, since
         * our tokenizer is dumb, we need to keep this working!
         */
        next_character          = this->GetCharacter();
        if(
            (
                (current_character  == this->current_rules->comment_token)               &&
                (next_character     == this->current_rules->line_comment_hint_token)
            )
            ||
            (
                (current_character  == this->current_rules->comment_token)               &&
                (next_character     == this->current_rules->delimited_comment_hint_token)
            )
        )
        {
            /* NOTE: this skips to the comments. */
            goto inside_comment_token_block_post_next_character;
        }
        else
        {
            /* Since we found out the next character, we need to return one and leave the
             * next character to the tokenizer to take cara later. */
            this->Rewind(1);
            key->push_back(static_cast<char>(current_character));
        }
    }
    else if(
        current_character == this->current_rules->comment_token
    )
    {
        next_character = this->GetCharacter();
        inside_comment_token_block_post_next_character:
        this->WasteComment(next_character);
        goto top;
    }
    else
    {
        this->GetTokenAny(key, current_character);
    }
skip_everything:
    std::cout << __PRETTY_FUNCTION__ << ": Adquired Token = " << *key << "\n";
    return;
}