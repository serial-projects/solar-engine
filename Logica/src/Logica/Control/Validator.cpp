#include "Logica/Control/Validator.hpp"
#include <cstdarg>

Logica::Control::Validator::Validator()
{
    this->at_error_callback = std::function<void(Logica::Control::Validator::Content*, void*)>();
    this->userdata          = nullptr;
    this->content           = Logica::Control::Validator::Content();
}

void Logica::Control::Validator::SetErrorCallback(
    std::function<void(Logica::Control::Validator::Content*, void*)> 
        when_error_callback_f
)
{
    this->at_error_callback = when_error_callback_f;
}

void Logica::Control::Validator::SetUserDataForCallback(
    void* userdata
)
{
    this->userdata = userdata;
}

void Logica::Control::Validator::SetError(
    const Logica::Types::Basic::U8 code,
    const Logica::Types::Basic::CH8* format,
    ...
)
{
    std::va_list args;
    va_start(args, format);
    
    /* TODO: allow for configuration for this buffer size, which is 512 ALWAYS. */
    Logica::Types::Basic::CH8 __buffer[512] = {};
    std::vsnprintf(__buffer, 512, format, args);

    this->content.buffer = Logica::Types::Basic::String(__buffer);
    this->content.code = code;

    /* NOTE: finally call the call back (if possible): */
    if(this->at_error_callback)
        this->at_error_callback(
            &this->content,
            this->userdata
        );
}

Logica::Types::Basic::String& Logica::Control::Validator::GetBuffer()
{
    return this->content.buffer;
}

Logica::Types::Basic::U8 Logica::Control::Validator::GetCode()
{
    return this->content.code;
}