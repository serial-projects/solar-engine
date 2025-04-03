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
            namespace InstanceErrors
            {
                enum InstanceErrors
                {
                    /**
                     * \brief When everything is fine.
                     */
                    Ok                      = 0,
                    
                    /**
                     * \brief For when the string ends prematurely, that is, while parsing and
                     * getting characters for the string an EOF is found, that means the string
                     * is prematurely over and the delimiters were NOT hit (and will never hit).
                     */
                    PrematureStringEnd,

                    /**
                     * \brief Usually used when a token is very unexpected or contradictory on the
                     * rules itself, for example, suppose the '#' is a comment token and the line
                     * version is '##', but we got '#$', this will trigger an error.
                     */
                    UnexpectedToken,

                    /**
                     * \brief Unreacheable code.
                     */
                    Unknown                 = UINT8_MAX
                };
            };

            /**
             * \brief Enumerates all the states of the Instance.
             */
            namespace InstanceState
            {
                enum InstanceState
                {
                    /**
                     * \brief This and Unknown are unreacheable, but if for some reason you want to
                     * customize the state (Maybe?), this state is valid?
                     */
                    Nothing         = 0,

                    /**
                     * \brief When the machine is executing properly.
                     */
                    Running,

                    /**
                     * \brief When the machine has finished, that is, everything is done.
                     */
                    Finished,

                    /**
                     * \brief When the machine found a runtime error.
                     */
                    Died,

                    /**
                     * \brief Impossible code.
                     */
                    Unknown         = UINT8_MAX
                };
            };

            class Instance
            {
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
                 * \brief Keep the state of the machine, since the tokenizer is a machine.
                 */
                Logica::Types::Basic::U8            state = 1;

                void Rewind(
                    const Logica::Types::Basic::U8 amount
                );
                
                Logica::Types::Basic::I32 GetCharacter();

                void GetTokenStringLiteral(
                    Logica::Types::Basic::String* key
                );
                
                void GetTokenString(
                    Logica::Types::Basic::String* key,
                    const Logica::Types::Basic::I32 entrypoint_token
                );
                
                void GetTokenAny(
                    Logica::Types::Basic::String* key,
                    const Logica::Types::Basic::I32 entrypoint_token
                );

                void WasteDelimitedComment();

                void WasteLineComment();
                
                void WasteComment(
                    Logica::Types::Basic::I32 hint
                );

                public:
                Instance();

                Logica::Control::Validator validator;

                void SetBuffer(
                    Logica::Types::Stream::Buffer* buffer
                );
                
                void SetRules(
                    Logica::Texting::Tokenizer::Rules* rules
                );

                Logica::Types::Basic::U8 GetState();
                Logica::Types::Basic::U32 GetCurrentLine();
                
                void GetToken(
                    Logica::Types::Basic::String* key
                );
            };
        };
    };
};


#endif