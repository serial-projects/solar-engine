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
            /**
             * \brief Contains all the rules for the tokenizer to use.
             */
            struct Rules
            {
                /**
                 * \brief Contains everything about the types of tokens.
                 */
                enum CharacterTypes
                {
                    NOTHING             = 0,
                    TOKEN_DELIMITER,
                    STRING_DELIMITER,
                    HIGHLIGHT_TOKEN
                };
                std::function<Logica::Types::Basic::U8(const Logica::Types::Basic::I32)> get_character_type;
                Logica::Types::Basic::I32   comment_token;
                Logica::Types::Basic::I32   line_comment_hint_token;
                Logica::Types::Basic::I32   delimited_comment_hint_token;
                Logica::Types::Basic::I32   delimited_comment_closure_token;
            };
        };
    };
};

#endif