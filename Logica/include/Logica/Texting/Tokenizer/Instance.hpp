#ifndef LogicaTextingTokenizerInstance_hpp
#define LogicaTextingTokenizerInstance_hpp

#include "Logica/Types.hpp"
#include "Logica/Texting/Tokenizer/Rules.hpp"
#include "Logica/Control/Validator.hpp"

namespace Logica
{
    namespace Texting
    {
        namespace Tokenizer
        {
            class Instance
            {
                /*** PRIVATE SEGMENT */
                private:
                Logica::Types::Stream::Buffer*      working_buffer;
                Logica::Types::Basic::U32           line_counter = 0;
                Logica::Texting::Tokenizer::Rules*  current_rules;

                /**
                 * \brief Use this to remove the possibility of double line after an rewind, 
                 * the line counter will ONLY increment when the buffer position is bigger than the 
                 * max position.
                 */
                Logica::Types::Basic::Size          newline_max_position = 0;

                /**
                 * \brief Returns on the buffer by a certain amount.
                 */
                void Rewind(
                    const Logica::Types::Basic::U8 amount
                );
                
                /**
                 * \brief Get the character from the buffer and automatically compute the newline.
                 */
                Logica::Types::Basic::I32 GetCharacter();

                /**
                 * \brief When the token is a literal, this subfunction will operate.
                 * string itself.
                 */
                void GetTokenStringLiteral(
                    Logica::Types::Basic::String* key
                );
                
                /**
                 * \brief When the token is a literal.
                 */
                void GetTokenString(
                    Logica::Types::Basic::String* key,
                    const Logica::Types::Basic::I32 entrypoint_token
                );
                
                /**
                 * \brief For any token.
                 */
                void GetTokenAny(
                    Logica::Types::Basic::String* key,
                    const Logica::Types::Basic::I32 entrypoint_token
                );

                /**
                 * \brief Waste an delimited comment.
                 */
                void WasteDelimitedComment();

                /**
                 * \brief Waste an line comment.
                 */
                void WasteLineComment();
                
                /**
                 * \brief Determine what type of comment it is by the hint and waste it.
                 */
                void WasteComment(
                    Logica::Types::Basic::I32 hint
                );
                
                /*** PUBLIC SEGMENT */
                public:
                Instance();

                /**
                 * \brief Contains the values the tokenizer is holding.
                 */
                Logica::Control::Validator validator;

                /**
                 * \brief This enum contains all the states the tokenizer can be operating.
                 */
                enum States
                {
                    /**
                     * \brief This and Unknown are unreacheable, but if for some reason you want to
                     * customize the state (Maybe?), this state is valid?
                     */
                    NOTHING         = 0,

                    /**
                     * \brief When the machine is executing properly.
                     */
                    RUNNING,

                    /**
                     * \brief When the machine has finished, that is, everything is done.
                     */
                    FINISHED,

                    /**
                     * \brief When the machine found a runtime error.
                     */
                    DIED
                };

                Logica::Texting::Tokenizer::Instance::States state = NOTHING;

                /**
                 * \brief This enum contains all the errors the machine can find.
                 */
                enum Errors
                {
                    /**
                     * \brief When everything is fine.
                     */
                    OK = 0,
                    
                    /**
                     * \brief For when the string ends prematurely, that is, while parsing and
                     * getting characters for the string an EOF is found, that means the string
                     * is prematurely over and the delimiters were NOT hit (and will never hit).
                     */
                    PREMATURE_STRING_END,

                    /**
                     * \brief Usually used when a token is very unexpected or contradictory on the
                     * rules itself, for example, suppose the '#' is a comment token and the line
                     * version is '##', but we got '#$', this will trigger an error.
                     */
                    UNEXPECTED_TOKEN
                };

                /**
                 * \brief Set the buffer the tokenizer will use.
                 */
                void SetBuffer(
                    Logica::Types::Stream::Buffer* buffer
                );
                
                /**
                 * \brief Set the rules the tokenizer will use.
                 */
                void SetRules(
                    Logica::Texting::Tokenizer::Rules* rules
                );

                /**
                 * \brief Returns the current line the tokenzier is.
                 */
                Logica::Types::Basic::U32 GetCurrentLine();
                
                /**
                 * \brief Gets the new token.
                 */
                void GetToken(
                    Logica::Types::Basic::String* key
                );
            };
        };
    };
};


#endif