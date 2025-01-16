#ifndef LogicaTextingTokenizerRules_hpp
#define LogicaTextingTokenizerRules_hpp

#include "Logica/Types.hpp"
#include <functional>

namespace Logica
{
    namespace Texting 
    {
        namespace Tokenizer
        {
            /// @brief The type of functions for the tokenizer.
            namespace RulesFunctions
            {
                typedef std::function<Logica::Types::Basic::Result(Logica::Types::Basic::I32)> GenericTokenCheck;
                typedef Logica::Texting::Tokenizer::RulesFunctions::GenericTokenCheck IsTokenDelimiter;
                typedef Logica::Texting::Tokenizer::RulesFunctions::GenericTokenCheck IsTokenStringDelimiter;
                typedef Logica::Texting::Tokenizer::RulesFunctions::GenericTokenCheck IsTokenToHighlight;
            };

            /* TODO: on the future, make the rules more flexible. */

            /// @brief Instance rules for the tokenizer.
            typedef struct Rules
            {
                /// @brief Token delimiters is the tokens that stay between an token, for           \a
                /// "hello token", the token delimiter is: ' ' after 'o' and it sets the bridge     \a
                /// to divide "hello" from "token", so this must be: [' ', '\t' and etc.]
                Logica::Texting::Tokenizer::RulesFunctions::IsTokenDelimiter is_token_delimiter;

                /// @brief What indicates the string to be, tokens like: ['"' or '\'']
                Logica::Texting::Tokenizer::RulesFunctions::IsTokenStringDelimiter is_token_string_delimiter;

                /// @brief Tokens to high light will be put on their own token and will break       \a
                /// an is_token_delimiters!
                Logica::Texting::Tokenizer::RulesFunctions::IsTokenToHighlight is_token_highlight;

                /// @brief Return whether the token is a initializer for an comment, for example:   \a
                /// '#' is a possible token or maybe '/', but this still leaves the question of:    \a
                /// is this a single line or a delimited? for that, the other comment functions are \a
                /// used.
                Logica::Types::Basic::CH8 comment_starter;

                /// @brief Return whether the token is indicating an single line comment            \a
                /// for example, an C comment is '//' for a single line. BUT, this isn't a rule     \a
                /// since an '#' can be just a line and '#*' can be the the delimited. This depends \a
                /// on the syntax.
                Logica::Types::Basic::CH8 comment_single_line_hint;

                /// @brief Return whether the token is indicating an delimited comment, for example \a
                /// in C, an delimited comment would be '/' + '*', this is an required thing.
                Logica::Types::Basic::CH8 comment_delimited_hint;

                Rules();
            } Rules;
        };
    };
};

#endif