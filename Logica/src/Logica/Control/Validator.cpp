#include "Logica/Control/Validator.hpp"
#include <cstdarg>

/* TODO: remove the debug! */
#include <iostream>

Logica::Control::ValidatorValues::ValidatorValues()
{
    this->code = 0;
    this->buffer = Logica::Types::Basic::String();
}

Logica::Control::Validator::Validator()
{
    this->when_error_callback_f = nullptr;
    this->userdata = nullptr;
}

void Logica::Control::Validator::SetErrorCallback(
    Logica::Control::ValidatorWhenErrorCallback when_error_callback_f
)
{
    this->when_error_callback_f = when_error_callback_f;
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

    this->values.buffer = Logica::Types::Basic::String(__buffer);
    this->values.code = code;

    std::cout
        << __PRETTY_FUNCTION__
        << ": "
        << this->values.buffer
        << "\n";

    /* NOTE: finally call the call back (if possible): */
    if(this->when_error_callback_f != nullptr)
        this->when_error_callback_f(
            &this->values,
            this->userdata
        );
}

Logica::Types::Basic::String& Logica::Control::Validator::GetBuffer()
{
    return this->values.buffer;
}

Logica::Types::Basic::U8 Logica::Control::Validator::GetCode()
{
    return this->values.code;
}