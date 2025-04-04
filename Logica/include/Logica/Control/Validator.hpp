#ifndef LogicaTypesControlValidator_hpp
#define LogicaTypesControlValidator_hpp

#include "Logica/Types.hpp"
#include <functional>

namespace Logica
{
    namespace Control
    {
        struct ValidatorContent
        {
            Logica::Types::Basic::String        err_log;
            Logica::Types::Basic::String        warn_log;
            Logica::Types::Basic::U8            code = 0;
        };

        namespace ValidatorFunctions
        {
            typedef std::function<void(Logica::Control::ValidatorContent* content, void* userdata)> ErrorCallback;
            typedef std::function<void(Logica::Control::ValidatorContent* content, void* userdata)> WarningCallback;
        }

        class Validator
        {
            public:

            /**
             * \brief Contains the error message string and code.
             */
            struct Content
            {
                Logica::Types::Basic::String    error_message;
                Logica::Types::Basic::String    warn_message;
                Logica::Types::Basic::U8        code = 0;
            };

            /**
             * \brief The content the validator holds, this is also passed to the callback functions
             * and is a "slot" for the validator.
             */
            Logica::Control::Validator::Content content;

            /**
             * \brief Standard type for the Callback.
             */
            typedef std::function<void(Logica::Control::Validator::Content*, void*)>
                Callback;

            /* Assign Functions: */
            void AssignErrorCallback(Logica::Control::Validator::Callback callback)     { this->error_callback = callback; };
            void AssignWarningCallback(Logica::Control::Validator::Callback callback)   { this->warning_callback = callback; };
            void AssignUserData(void* userdata)                                         { this->userdata = userdata; };

            /* Report Functions: */
            void ReportError(const Logica::Types::Basic::U8 code, const Logica::Types::Basic::CH8* format, ...);
            void ReportWarning(const Logica::Types::Basic::CH8* format, ...);
            
            /* Get and some other functions: */
            inline Logica::Types::Basic::U8        GetCode()        { return this->content.code; };
            inline Logica::Types::Basic::String&   GetErrorLog()    { return this->content.error_message; };
            inline Logica::Types::Basic::String&   GetWarningLog()  { return this->content.warn_message; };

            private:
            Logica::Control::Validator::Callback    error_callback;
            Logica::Control::Validator::Callback    warning_callback;
            void*                                   userdata;
        };
    };
};

#endif