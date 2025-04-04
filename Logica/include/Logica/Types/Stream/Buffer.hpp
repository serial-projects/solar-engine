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
            class Buffer
            {
                public:
                    /**
                     * Set all the callback functions inside the class.
                     */
                    typedef std::function<void(void*)> InitFunction;
                    typedef std::function<void(void*, const Logica::Types::Basic::Size)> SetPositionFunction;
                    typedef std::function<Logica::Types::Basic::Size(void*)> GetPositionFunction;
                    typedef std::function<void(void*)> CloseFunction;
                    typedef std::function<Logica::Types::Basic::U8(void*)>  ReadU8Function;
                    typedef std::function<Logica::Types::Basic::U16(void*)> ReadU16Function;
                    typedef std::function<Logica::Types::Basic::U32(void*)> ReadU32Function;
                    typedef std::function<Logica::Types::Basic::U64(void*)> ReadU64Function;
                    typedef std::function<Logica::Types::Basic::I8(void*)>  ReadI8Function;
                    typedef std::function<Logica::Types::Basic::I16(void*)> ReadI16Function;
                    typedef std::function<Logica::Types::Basic::I32(void*)> ReadI32Function;
                    typedef std::function<Logica::Types::Basic::I64(void*)> ReadI64Function;

                    void AssignInit(
                        Logica::Types::Stream::Buffer::InitFunction init
                    );
                    
                    void AssignSetPosition(
                        Logica::Types::Stream::Buffer::SetPositionFunction set_position
                    );

                    void AssignGetPosition(
                        Logica::Types::Stream::Buffer::GetPositionFunction get_position
                    );
                    
                    void AssignClose(
                        Logica::Types::Stream::Buffer::CloseFunction close
                    );

                    void AssignReadU8(
                        Logica::Types::Stream::Buffer::ReadU8Function readu8
                    );

                    void AssignReadU16(
                        Logica::Types::Stream::Buffer::ReadU16Function readu16
                    );

                    void AssignReadU32(
                        Logica::Types::Stream::Buffer::ReadU32Function readu32
                    );

                    void AssignReadU64(
                        Logica::Types::Stream::Buffer::ReadU64Function readu64
                    );

                    void AssignReadI8(
                        Logica::Types::Stream::Buffer::ReadI8Function readi8
                    );

                    void AssignReadI16(
                        Logica::Types::Stream::Buffer::ReadI16Function readi16
                    );

                    void AssignReadI32(
                        Logica::Types::Stream::Buffer::ReadI32Function readi32
                    );

                    void AssignReadI64(
                        Logica::Types::Stream::Buffer::ReadI64Function readi64
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
                private:
                    Logica::Types::Stream::Buffer::InitFunction         init;
                    Logica::Types::Stream::Buffer::SetPositionFunction  set_position;
                    Logica::Types::Stream::Buffer::GetPositionFunction  get_position;
                    Logica::Types::Stream::Buffer::CloseFunction        close;
                    Logica::Types::Stream::Buffer::ReadU8Function       readu8;
                    Logica::Types::Stream::Buffer::ReadU16Function      readu16;
                    Logica::Types::Stream::Buffer::ReadU32Function      readu32;
                    Logica::Types::Stream::Buffer::ReadU64Function      readu64;
                    Logica::Types::Stream::Buffer::ReadI8Function       readi8;
                    Logica::Types::Stream::Buffer::ReadI16Function      readi16;
                    Logica::Types::Stream::Buffer::ReadI32Function      readi32;
                    Logica::Types::Stream::Buffer::ReadI64Function      readi64;
                    void*                                               userdata;
            };
        };
    };
};

#endif