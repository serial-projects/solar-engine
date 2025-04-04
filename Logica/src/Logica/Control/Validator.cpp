#include "Logica/Control/Validator.hpp"
#include "Logica/Config.hpp"

#include <cstdarg>

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

    this->content.error_message     = buffer;
    this->content.code              = code;

    /* Call the callbacks? */
    if(this->error_callback)
        this->error_callback(
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

    this->content.warn_message = buffer;

    /* Call the callbacks? */
    if(this->warning_callback)
        this->warning_callback(
            &this->content,
            this->userdata
        );
}
