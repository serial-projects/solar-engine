#include "Logica/Control/Validator.hpp"
#include "Logica/Config.hpp"

#include <cstdarg>

void Logica::Control::Validator::AssignErrorCallback(
    Logica::Control::ValidatorFunctions::ErrorCallback error_callback_f
)
{
    this->error_callback_f = error_callback_f;
}

void Logica::Control::Validator::AssignWarningCallback(
    Logica::Control::ValidatorFunctions::WarningCallback warning_callback_f
)
{
    this->warning_callback_f = warning_callback_f;
}

void Logica::Control::Validator::AssignUserData(
    void* userdata
)
{
    this->userdata = userdata;
}

/* Report Functions: */
void Logica::Control::Validator::ReportError(
    const Logica::Types::Basic::U8 code,
    const Logica::Types::Basic::CH8* format,
    ...
)
{
    /* Initialize the list: */
    std::va_list arguments;
    va_start(arguments, format);
    
    /* Start the buffer here: */
    Logica::Types::Basic::CH8 buffer[LOGICA_CONTROL_VALIDATOR_REPORT_ERROR_BUFFER_SIZE] = {};
    std::vsnprintf(
        buffer,
        LOGICA_CONTROL_VALIDATOR_REPORT_ERROR_BUFFER_SIZE,
        format,
        arguments
    );

    this->content.err_log           = buffer;
    this->content.code              = code;

    /* Call the callbacks? */
    if(this->error_callback_f)
        this->error_callback_f(
            &this->content,
            this->userdata
        );
}

void Logica::Control::Validator::ReportWarning(
    const Logica::Types::Basic::CH8* format,
    ...
)
{
    /* Initialize the list: */
    std::va_list arguments;
    va_start(arguments, format);

    /* Start the buffer here: */
    Logica::Types::Basic::CH8 buffer[LOGICA_CONTROL_VALIDATOR_REPORT_WARNING_BUFFER_SIZE] = {};
    std::vsnprintf(
        buffer,
        LOGICA_CONTROL_VALIDATOR_REPORT_WARNING_BUFFER_SIZE,
        format,
        arguments
    );

    this->content.warn_log          = buffer;

    /* Call the callbacks? */
    if(this->warning_callback_f)
        this->warning_callback_f(
            &this->content,
            this->userdata
        );
}

/* Get and some other functions: */
Logica::Types::Basic::U8 Logica::Control::Validator::GetCode()
{
    return this->content.code;
}

Logica::Types::Basic::String& Logica::Control::Validator::GetErrorLog()
{
    return this->content.err_log;
}

Logica::Types::Basic::String& Logica::Control::Validator::GetWarningLog()
{
    return this->content.warn_log;
}