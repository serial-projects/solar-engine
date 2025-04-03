#ifndef LogicaTypesStreamBuffer_hpp
#define LogicaTypesStreamBuffer_hpp

#include "Logica/Types/Basic.hpp"
#include <functional>

namespace Logica
{
    namespace Types
    {
        namespace Stream
        {
            namespace BufferFunctions
            {
                typedef std::function<void(void*)>                                      Init;
                typedef std::function<void(void*, const Logica::Types::Basic::Size)>    SetPosition;
                typedef std::function<Logica::Types::Basic::Size(void*)>                GetPosition;
                typedef std::function<void(void*)>                                      Close;

                /* Read Functions: */

                typedef std::function<Logica::Types::Basic::U8(void*)>  ReadU8;
                typedef std::function<Logica::Types::Basic::U16(void*)> ReadU16;
                typedef std::function<Logica::Types::Basic::U32(void*)> ReadU32;
                typedef std::function<Logica::Types::Basic::U64(void*)> ReadU64;
                
                typedef std::function<Logica::Types::Basic::I8(void*)>  ReadI8;
                typedef std::function<Logica::Types::Basic::I16(void*)> ReadI16;
                typedef std::function<Logica::Types::Basic::I32(void*)> ReadI32;
                typedef std::function<Logica::Types::Basic::I64(void*)> ReadI64;
            };

            class Buffer
            {
                private:
                Logica::Types::Stream::BufferFunctions::Init        init_f;
                Logica::Types::Stream::BufferFunctions::SetPosition set_position_f;
                Logica::Types::Stream::BufferFunctions::GetPosition get_position_f;
                Logica::Types::Stream::BufferFunctions::Close       close_f;
                Logica::Types::Stream::BufferFunctions::ReadU8      readu8_f;
                Logica::Types::Stream::BufferFunctions::ReadU16     readu16_f;
                Logica::Types::Stream::BufferFunctions::ReadU32     readu32_f;
                Logica::Types::Stream::BufferFunctions::ReadU64     readu64_f;
                Logica::Types::Stream::BufferFunctions::ReadI8      readi8_f;
                Logica::Types::Stream::BufferFunctions::ReadI16     readi16_f;
                Logica::Types::Stream::BufferFunctions::ReadI32     readi32_f;
                Logica::Types::Stream::BufferFunctions::ReadI64     readi64_f;
                void*                                               userdata;

                public:

                /* Assign Functions: */
                void AssignInit(
                    Logica::Types::Stream::BufferFunctions::Init init_f
                );
                
                void AssignSetPosition(
                    Logica::Types::Stream::BufferFunctions::SetPosition set_position_f
                );

                void AssignGetPosition(
                    Logica::Types::Stream::BufferFunctions::GetPosition get_position_f
                );
                
                void AssignClose(
                    Logica::Types::Stream::BufferFunctions::Close close_f
                );

                void AssignReadU8(
                    Logica::Types::Stream::BufferFunctions::ReadU8 readu8_f
                );

                void AssignReadU16(
                    Logica::Types::Stream::BufferFunctions::ReadU16 readu16_f
                );

                void AssignReadU32(
                    Logica::Types::Stream::BufferFunctions::ReadU32 readu32_f
                );

                void AssignReadU64(
                    Logica::Types::Stream::BufferFunctions::ReadU64 readu64_f
                );

                void AssignReadI8(
                    Logica::Types::Stream::BufferFunctions::ReadI8 readi8_f
                );

                void AssignReadI16(
                    Logica::Types::Stream::BufferFunctions::ReadI16 readi16_f
                );

                void AssignReadI32(
                    Logica::Types::Stream::BufferFunctions::ReadI32 readi32_f
                );

                void AssignReadI64(
                    Logica::Types::Stream::BufferFunctions::ReadI64 readi64_f
                );

                void AssignUserData(
                    void* userdata
                );

                /* The Buffer Functions: */
                void Init();
                
                void SetPosition(
                    const Logica::Types::Basic::Size position
                );
                
                Logica::Types::Basic::Size GetPosition();
                
                void Close();

                Logica::Types::Basic::U8 ReadU8();

                Logica::Types::Basic::U16 ReadU16();
                
                Logica::Types::Basic::U32 ReadU32();
                
                Logica::Types::Basic::U64 ReadU64();
                
                Logica::Types::Basic::I8 ReadI8();
                
                Logica::Types::Basic::I16 ReadI16();
                
                Logica::Types::Basic::I32 ReadI32();
                
                Logica::Types::Basic::I64 ReadI64();
            };
        };
    };
};

#endif