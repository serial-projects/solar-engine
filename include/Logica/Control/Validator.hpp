#ifndef LogicaControlValidator_hpp
#define LogicaControlValidator_hpp

#include "Logica/Types/Basic.hpp"
#include "Logica/Types/Functions.hpp"

/* Validator Macro Helpers: */

#define LogicaControlValidatorPerformActionAndProceedIfValidated(action, validator)                 \
    action;                                                                                         \
    if(validator->code != 0) return;

#define LogicaControlValidatorPerformActionAndHandleFail(action, validator, error_branch)           \
    action;                                                                                         \
    if(validator->code != 0) error_branch;

namespace Logica
{
    namespace Control
    {
        /// @brief NOTE: use Validator class, this is NOT to be used as it just contains the code
        /// and the buffer for the validator, for all the functions, use the class!
        struct ValidatorValues
        {
            Logica::Types::Basic::U8        code;
            Logica::Types::Basic::String    buffer;
            ValidatorValues();
        };

        typedef void(*ValidatorWhenErrorCallback)(Logica::Control::ValidatorValues* validator, void* userdata);

        /// @brief Validator is an error storage component, that is, when there is an error
        /// it will keep it to VALIDATE certain actions later.
        struct Validator
        {
            /* Code & Error Buffer: */

            /// @brief The values that are passed to the callback (in example)
            Logica::Control::ValidatorValues values;

            /* Callbacks: */

            /// @brief The attached function to call when error happens.
            Logica::Control::ValidatorWhenErrorCallback when_error_callback_f;

            /// @brief The attached pointer for some data to the when_error_callback_f()
            void* userdata;

            /* Construction: */

            /// @brief Validator builder.
            Validator();

            /* Set functions: */

            /// @brief When attached, it will callback an function.
            /// @param when_error_callback_f function to attach.
            void SetErrorCallback(Logica::Control::ValidatorWhenErrorCallback when_error_callback_f);

            /// @brief an customized parameter data for your validator, useful for error handling.
            /// @param userdata the user data (void*) format.
            void SetUserDataForCallback(void* userdata);

            /// @brief Set the current state of the validator.
            /// @param code the code (0 is usually Ok).
            /// @param format the string to be formatted
            /// @param ... anything else
            void SetError(const Logica::Types::Basic::U8 code, const Logica::Types::Basic::CH8* format, ...);
            
            /* Get functions: */

            /// @brief Returns the buffer.
            /// @return the reference for the string.
            Logica::Types::Basic::String& GetBuffer();

            /// @brief Returns the code.
            /// @return the code.
            Logica::Types::Basic::U8 GetCode();
        };
    };
};

#endif