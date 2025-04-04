#include "Logica/Types/Stream/Buffer.hpp"

/*
 * Assign Functions:
 */
#define MergeNames(x, y) x##y
#define AssignFunctionFactory(uppercase_n, lowercase_n, type)                                       \
    void Logica::Types::Stream::Buffer::Assign##uppercase_n(                                        \
        Logica::Types::Stream::Buffer::type lowercase_n                                             \
    )                                                                                               \
    {                                                                                               \
        this->lowercase_n = lowercase_n;                                                            \
    }                                                                                               

AssignFunctionFactory(Init, init, InitFunction);
AssignFunctionFactory(Close, close, CloseFunction);
AssignFunctionFactory(GetPosition, get_position, GetPositionFunction);
AssignFunctionFactory(SetPosition, set_position, SetPositionFunction);
AssignFunctionFactory(ReadU8, readu8, ReadU8Function);
AssignFunctionFactory(ReadU16, readu16, ReadU16Function);
AssignFunctionFactory(ReadU32, readu32, ReadU32Function);
AssignFunctionFactory(ReadU64, readu64, ReadU64Function);
AssignFunctionFactory(ReadI8, readi8, ReadI8Function);
AssignFunctionFactory(ReadI16, readi16, ReadI16Function);
AssignFunctionFactory(ReadI32, readi32, ReadI32Function);
AssignFunctionFactory(ReadI64, readi64, ReadI64Function);
void Logica::Types::Stream::Buffer::AssignUserData(void* userdata)                                  { this->userdata = userdata; }

/**
 * Connectors are defined here:
 */

void Logica::Types::Stream::Buffer::Init()                                                          { this->init(this->userdata); }
void Logica::Types::Stream::Buffer::SetPosition(const Logica::Types::Basic::Size position)          { this->set_position(this->userdata, position); }
Logica::Types::Basic::Size Logica::Types::Stream::Buffer::GetPosition()                             { return this->get_position(this->userdata); }
void Logica::Types::Stream::Buffer::Close()                                                         { this->close(this->userdata);              }
Logica::Types::Basic::U8 Logica::Types::Stream::Buffer::ReadU8()                                    { return this->readu8(this->userdata);      }
Logica::Types::Basic::U16 Logica::Types::Stream::Buffer::ReadU16()                                  { return this->readu16(this->userdata);     }
Logica::Types::Basic::U32 Logica::Types::Stream::Buffer::ReadU32()                                  { return this->readu32(this->userdata);     }
Logica::Types::Basic::U64 Logica::Types::Stream::Buffer::ReadU64()                                  { return this->readu64(this->userdata);     }
Logica::Types::Basic::I8 Logica::Types::Stream::Buffer::ReadI8()                                    { return this->readi8(this->userdata);      }
Logica::Types::Basic::I16 Logica::Types::Stream::Buffer::ReadI16()                                  { return this->readi16(this->userdata);     }
Logica::Types::Basic::I32 Logica::Types::Stream::Buffer::ReadI32()                                  { return this->readi32(this->userdata);     }
Logica::Types::Basic::I64 Logica::Types::Stream::Buffer::ReadI64()                                  { return this->readi64(this->userdata);     }