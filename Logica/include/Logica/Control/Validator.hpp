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
            private:
            Logica::Control::ValidatorFunctions::ErrorCallback      error_callback_f;
            Logica::Control::ValidatorFunctions::WarningCallback    warning_callback_f;
            void*                                                   userdata;
            public:
            Logica::Control::ValidatorContent                       content;

            /* Assign Functions: */
            void AssignErrorCallback(Logica::Control::ValidatorFunctions::ErrorCallback error_callback_f);
            void AssignWarningCallback(Logica::Control::ValidatorFunctions::WarningCallback warning_callback_f);
            void AssignUserData(void* userdata);

            /* Report Functions: */
            void ReportError(const Logica::Types::Basic::U8 code, const Logica::Types::Basic::CH8* format, ...);
            void ReportWarning(const Logica::Types::Basic::CH8* format, ...);
            
            /* Get and some other functions: */
            Logica::Types::Basic::U8 GetCode();
            Logica::Types::Basic::String& GetErrorLog();
            Logica::Types::Basic::String& GetWarningLog();
        };
    };
};

#endif