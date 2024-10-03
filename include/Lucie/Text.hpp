#ifndef LucieText_hpp
#define LucieText_hpp

#include "Lucie/Types.hpp"

namespace Lucie
{
    namespace Text
    {
        typedef std::vector<Lucie::String> Tokens;

        /* TOKENIZER STATES: */
        enum TokenizerStates
        {
            Default                             = 0,
            String,
            Literal,
            BeginComment,
            InlineComment,
            DelimitedComment,
            DelimitedCommentClosure
        };

        /* TOKENIZER: */
        typedef struct Tokenizer
        {
            Lucie::Text::Tokens tokens;
            Lucie::String       accumulator;
            Lucie::PackedData8  mode;
            Lucie::Character    strdel;
        } Tokenizer;
        Lucie::Text::Tokenizer* TokenizerNew();
        void TokenizerDestroy(Lucie::Text::Tokenizer* tokenizer);
        void TokenizerInit(Lucie::Text::Tokenizer* tokenizer);
        void TokenizerPushAccumulatorIntoTokens(Lucie::Text::Tokenizer* tokenizer);
        void TokenizerFeed(Lucie::Text::Tokenizer* tokenizer, const Lucie::String buffer);
        void TokenizerDigest(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
        void TokenizerDigestDefault(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
        void TokenizerDigestString(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
        void TokenizerDigestLiteral(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
        void TokenizerDigestBeginComment(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
        void TokenizerDigestInlineComment(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
        void TokenizerDigestDelimitedComment(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
        void TokenizerDigestDelimitedCommentClosure(Lucie::Text::Tokenizer* tokenizer, const Lucie::Character ch);
    };
};

#endif