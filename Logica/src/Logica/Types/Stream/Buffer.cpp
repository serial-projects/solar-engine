#include "Logica/Types/Stream/Buffer.hpp"

/*
 * Assign Functions:
 */

void Logica::Types::Stream::Buffer::AssignInit(
    Logica::Types::Stream::BufferFunctions::Init init_f
)
{
    this->init_f = init_f;
}

void Logica::Types::Stream::Buffer::AssignSetPosition(
    Logica::Types::Stream::BufferFunctions::SetPosition set_position_f
)
{
    this->set_position_f = set_position_f;
}

void Logica::Types::Stream::Buffer::AssignGetPosition(
    Logica::Types::Stream::BufferFunctions::GetPosition get_position_f
)
{
    this->get_position_f = get_position_f;
}

void Logica::Types::Stream::Buffer::AssignClose(
    Logica::Types::Stream::BufferFunctions::Close close_f
)
{
    this->close_f = close_f;
}

void Logica::Types::Stream::Buffer::AssignReadU8(
    Logica::Types::Stream::BufferFunctions::ReadU8 readu8_f
)
{
    this->readu8_f = readu8_f;
}

void Logica::Types::Stream::Buffer::AssignReadU16(
    Logica::Types::Stream::BufferFunctions::ReadU16 readu16_f
)
{
    this->readu16_f = readu16_f;
}

void Logica::Types::Stream::Buffer::AssignReadU32(
    Logica::Types::Stream::BufferFunctions::ReadU32 readu32_f
)
{
    this->readu32_f = readu32_f;
}

void Logica::Types::Stream::Buffer::AssignReadU64(
    Logica::Types::Stream::BufferFunctions::ReadU64 readu64_f
)
{
    this->readu64_f = readu64_f;
}

void Logica::Types::Stream::Buffer::AssignReadI8(
    Logica::Types::Stream::BufferFunctions::ReadI8 readi8_f
)
{
    this->readi8_f = readi8_f;
}

void Logica::Types::Stream::Buffer::AssignReadI16(
    Logica::Types::Stream::BufferFunctions::ReadI16 readi16_f
)
{
    this->readi16_f = readi16_f;
}

void Logica::Types::Stream::Buffer::AssignReadI32(
    Logica::Types::Stream::BufferFunctions::ReadI32 readi32_f
)
{
    this->readi32_f = readi32_f;
}

void Logica::Types::Stream::Buffer::AssignReadI64(
    Logica::Types::Stream::BufferFunctions::ReadI64 readi64_f
)
{
    this->readi64_f = readi64_f;
}

void Logica::Types::Stream::Buffer::AssignUserData(
    void* userdata
)
{
    this->userdata = userdata;
}

/*
 * "API Functions" are declared here:
 */

void Logica::Types::Stream::Buffer::Init()
{
    this->init_f(this->userdata);
}

void Logica::Types::Stream::Buffer::SetPosition(
    const Logica::Types::Basic::Size position
)
{
    this->set_position_f(this->userdata, position);
}

Logica::Types::Basic::Size Logica::Types::Stream::Buffer::GetPosition()
{
    Logica::Types::Basic::Size value = this->get_position_f(this->userdata);
    return value;
}

void Logica::Types::Stream::Buffer::Close()
{
    this->close_f(this->userdata);
}

Logica::Types::Basic::U8 Logica::Types::Stream::Buffer::ReadU8()
{
    return this->readu8_f(this->userdata);
}

Logica::Types::Basic::U16 Logica::Types::Stream::Buffer::ReadU16()
{
    return this->readu16_f(this->userdata);
}

Logica::Types::Basic::U32 Logica::Types::Stream::Buffer::ReadU32()
{
    return this->readu32_f(this->userdata);
}

Logica::Types::Basic::U64 Logica::Types::Stream::Buffer::ReadU64()
{
    return this->readu64_f(this->userdata);
}

Logica::Types::Basic::I8 Logica::Types::Stream::Buffer::ReadI8()
{
    return this->readi8_f(this->userdata);
}

Logica::Types::Basic::I16 Logica::Types::Stream::Buffer::ReadI16()
{
    return this->readi16_f(this->userdata);
}

Logica::Types::Basic::I32 Logica::Types::Stream::Buffer::ReadI32()
{
    return this->readi32_f(this->userdata);
}

Logica::Types::Basic::I64 Logica::Types::Stream::Buffer::ReadI64()
{
    return this->readi64_f(this->userdata);
}