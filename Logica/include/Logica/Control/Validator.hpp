#ifndef LogicaControlValidator_hpp
#define LogicaControlValidator_hpp

#include "Logica/Types/Basic.hpp"
#include <functional>

namespace Logica
{
    namespace Control
    {
        /**
         * \brief Validator is an error storage component, that is, when there is an error
         * it will keep it to VALIDATE certain actions later.
         */
        class Validator
        {
            public:
                Validator();

                /**
                 * \brief An object that contains the code & current message.
                 */
                struct Content
                {
                    Logica::Types::Basic::U8        code = 0;
                    Logica::Types::Basic::String    buffer;
                };

                /**
                 * \brief Contains the current message and the code the validator is in.
                 */
                Logica::Control::Validator::Content content;

                /* Set functions: */

                /**
                 * \brief When attached, it will callback an function.
                 * \param when_error_callback_f function to attach.
                 */
                void SetErrorCallback(
                    std::function<void(Logica::Control::Validator::Content*, void*)> 
                        when_error_callback_f
                );

                /**
                 * \brief an customized parameter data for your validator, useful for error handling.
                 * \param userdata the user data (void*) format.
                 */
                void SetUserDataForCallback(void* userdata);

                /**
                 * \brief Set the current state of the validator.
                 * \param code the code (0 is usually Ok).
                 * \param format the string to be formatted
                 * \param ... anything else
                 */
                void SetError(
                    const Logica::Types::Basic::U8 code,
                    const Logica::Types::Basic::CH8* format,
                    ...
                );

                /**
                 *\brief Returns the buffer.
                 * \return the reference for the string.
                 */
                Logica::Types::Basic::String& GetBuffer();
                
                /**
                 * \brief Returns the code.
                 * \return the code.
                 */
                Logica::Types::Basic::U8 GetCode();
            private:
                /**
                 * \brief Callback for when some error happens.
                 */
                std::function<void(Logica::Control::Validator::Content*, void*)>
                    at_error_callback;

                /**
                 * \brief Pointer that is passed to the callback.
                 */
                void* userdata;
        };
    };
};

#endif