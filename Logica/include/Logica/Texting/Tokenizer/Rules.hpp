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
                /**
                 * \brief All the types for tokens.
                 */
                enum TokenTypes
                {
                    NO_TOKEN            = 0,
                    DELIMITER,
                    STRING,
                    HIGHLIGHT
                };
                
                /**
                 * \brief Get the token type, this must return the Rules::TokenType values.
                 */
                std::function<
                    Logica::Texting::Tokenizer::Rules::TokenTypes(Logica::Types::Basic::I32)
                > get_token_type;

                /// @brief Return whether the token is a initializer for an comment, for example:
                /// '#' is a possible token or maybe '/', but this still leaves the question of:
                /// is this a single line or a delimited? for that, the other comment functions are
                /// used.
                Logica::Types::Basic::CH8 comment_starter           = 0;

                /// @brief Return whether the token is indicating an single line comment            
                /// for example, an C comment is '//' for a single line. BUT, this isn't a rule     
                /// since an '#' can be just a line and '#*' can be the the delimited. This depends 
                /// on the syntax.
                Logica::Types::Basic::CH8 comment_single_line_hint  = 0;

                /// @brief Return whether the token is indicating an delimited comment, for example
                /// in C, an delimited comment would be '/' + '*', this is an required thing.
                Logica::Types::Basic::CH8 comment_delimited_hint    = 0;
            } Rules;
        };
    };
};

#endif