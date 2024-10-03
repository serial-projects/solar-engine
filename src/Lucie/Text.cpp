#include "Lucie/Text.hpp"
#include <iostream>

/*
 * TOKENIZER:
 */

Lucie::Text::Tokenizer* Lucie::Text::TokenizerNew()
{
    Lucie::Text::Tokenizer* tokenizer = new Lucie::Text::Tokenizer;
    return tokenizer;
}

void Lucie::Text::TokenizerDestroy(Lucie::Text::Tokenizer* tokenizer)
{
    delete tokenizer;
}

void Lucie::Text::TokenizerInit(Lucie::Text::Tokenizer* tokenizer)
{
    tokenizer->accumulator      = Lucie::String();
    tokenizer->tokens           = std::vector<Lucie::String>();
    tokenizer->mode             = 0;
    tokenizer->strdel           = 0;
}

void Lucie::Text::TokenizerPushAccumulatorIntoTokens(Lucie::Text::Tokenizer* tokenizer)
{
    if(tokenizer->accumulator.size() > 0)
    {
        tokenizer->tokens.push_back(tokenizer->accumulator);
        tokenizer->accumulator.clear();
    }
}

void Lucie::Text::TokenizerFeed(Lucie::Text::Tokenizer* tokenizer, const Lucie::String buffer)
{
    for(Lucie::Indexer index = 0; index < buffer.size(); index++)
        Lucie::Text::TokenizerDigest(
            tokenizer,
            buffer.at((std::size_t)index)
        );
    Lucie::Text::TokenizerPushAccumulatorIntoTokens(tokenizer);
}

void Lucie::Text::TokenizerDigest(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    switch(tokenizer->mode)
    {
        case Lucie::Text::TokenizerStates::Default:
            Lucie::Text::TokenizerDigestDefault(tokenizer, ch);
            break;
        case Lucie::Text::TokenizerStates::String:
            Lucie::Text::TokenizerDigestString(tokenizer, ch);
            break;
        case Lucie::Text::TokenizerStates::Literal:
            Lucie::Text::TokenizerDigestLiteral(tokenizer, ch);
            break;
        case Lucie::Text::TokenizerStates::BeginComment:
            Lucie::Text::TokenizerDigestBeginComment(tokenizer, ch);
            break;
        case Lucie::Text::TokenizerStates::InlineComment:
            Lucie::Text::TokenizerDigestInlineComment(tokenizer, ch);
            break;
        case Lucie::Text::TokenizerStates::DelimitedComment:
            Lucie::Text::TokenizerDigestDelimitedComment(tokenizer, ch);
            break;
        case Lucie::Text::TokenizerStates::DelimitedCommentClosure:
            Lucie::Text::TokenizerDigestDelimitedCommentClosure(tokenizer, ch);
            break;
        default:
            /* NOTE: decide if this is a fatal behavior using:
             * LUCIE_ENABLE_FATAL_BEHAVIOUR: (macro): this will enable crash inside lucie, aka abort(). 
             */
            #ifdef LUCIE_ENABLE_FATAL_BEHAVIOUR
                #include <iostream>
                std::cout 
                    << "LUCIE: fatal at " 
                    << __PRETTY_FUNCTION__ 
                    << ", invalid mode = " 
                    << tokenizer->mode
                    << "\n"
                abort();
            #else
                /* no fatalism, then move on: */
                tokenizer->mode = Lucie::Text::TokenizerStates::Default;
                break;
            #endif
    };
}

void Lucie::Text::TokenizerDigestDefault(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    if((ch == ' ' || ch == '\t' || ch == ','))
    {
        Lucie::Text::TokenizerPushAccumulatorIntoTokens(tokenizer);
    }
    else if((ch == '\n' || ch == '[' || ch == ']'))
    {
        Lucie::Text::TokenizerPushAccumulatorIntoTokens(tokenizer);
        tokenizer->tokens.push_back(Lucie::String{ch});
    }
    else if((ch == '"' || ch == '\''))
    {
        Lucie::Text::TokenizerPushAccumulatorIntoTokens(tokenizer);
        tokenizer->accumulator = ch;
        tokenizer->strdel = ch;
        tokenizer->mode = Lucie::Text::TokenizerStates::String;
    }
    else if((ch == '/'))
    {
        Lucie::Text::TokenizerPushAccumulatorIntoTokens(tokenizer);
        tokenizer->mode = Lucie::Text::TokenizerStates::BeginComment;
    }
    else
    {
        tokenizer->accumulator.push_back(ch);
    }
}

void Lucie::Text::TokenizerDigestString(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    if(tokenizer->strdel == ch)
    {
        tokenizer->accumulator.push_back(ch);
        tokenizer->mode = Lucie::Text::TokenizerStates::Default;
        Lucie::Text::TokenizerPushAccumulatorIntoTokens(tokenizer);
    }
    else
    {
        tokenizer->accumulator.push_back(ch);
    }
}

void Lucie::Text::TokenizerDigestLiteral(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    #ifdef LUCIE_ENABLE_FATAL_BEHAVIOUR
        std::cout
            << "LUCIE: function not implemented = "
            << __PRETTY_FUNCTION__
            << "\n";
        abort();
    #else
        /* NOTE: this will make the function intepret garbage: */
        tokenizer->mode = Lucie::Text::TokenizerStates::Default;
    #endif
}

void Lucie::Text::TokenizerDigestBeginComment(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    /* NOTE: account for the possible scenarios:
     * 1-) when the next character is: (/) -> this means the comment is inline;
     * 2-) when the next character is: (*) -> this means the comment is delimited;
     * 3-) when the next character is: (\n)-> this means the comment is not well formed.
     */
    if(ch == '/')       tokenizer->mode = Lucie::Text::TokenizerStates::InlineComment;
    else if(ch == '*')  tokenizer->mode = Lucie::Text::TokenizerStates::DelimitedComment;
    else
    {
        #ifdef LUCIE_ENABLE_FATAL_BEHAVIOUR
            std::cout
                << "LUCIE: bad format on "
                << __PRETTY_FUNCTION__
                << ", expected either: * or /, got = "
                << ch
                << "\n";
            abort();
        #else
            /* premature inline end? */
            if(ch == '\n') tokenizer->tokens.push_back(Lucie::String{'\n'});
            tokenizer->mode = Lucie::Text::TokenizerStates::Default;
        #endif
    }
}

void Lucie::Text::TokenizerDigestInlineComment(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    if(ch == '\n')
    {
        tokenizer->tokens.push_back(Lucie::String{'\n'});
        tokenizer->mode = Lucie::Text::TokenizerStates::Default;
    }
}

void Lucie::Text::TokenizerDigestDelimitedComment(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    if(ch == '*')
    {
        tokenizer->mode = Lucie::Text::TokenizerStates::DelimitedCommentClosure;
    }
    else if (ch == '\n')
    {
        tokenizer->tokens.push_back(Lucie::String{'\n'});
    }
}

void Lucie::Text::TokenizerDigestDelimitedCommentClosure(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch)
{
    if(ch == '/')
    {
        tokenizer->mode = Lucie::Text::TokenizerStates::Default;
    }
    else
    {
        if(ch == '\n')
            tokenizer->tokens.push_back(Lucie::String{'\n'});
        tokenizer->mode = Lucie::Text::TokenizerStates::DelimitedComment;
    }
}