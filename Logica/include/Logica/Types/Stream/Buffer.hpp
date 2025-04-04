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

                    /**
                     * \brief Assign an Init function for the Init(), this shall initialize your buffer.
                     */
                    void AssignInit(
                        Logica::Types::Stream::Buffer::InitFunction init
                    );
                    
                    /**
                     * \brief Assign an function to set the position in your buffer.
                     */
                    void AssignSetPosition(
                        Logica::Types::Stream::Buffer::SetPositionFunction set_position
                    );

                    /**
                     * \brief Assign an function to get the position in your buffer.
                     */
                    void AssignGetPosition(
                        Logica::Types::Stream::Buffer::GetPositionFunction get_position
                    );
                    
                    /**
                     * \brief Assign an function to close your buffer.
                     */
                    void AssignClose(
                        Logica::Types::Stream::Buffer::CloseFunction close
                    );

                    /**
                     * \brief Assign an function to read an U8 inside your buffer.
                     */
                    void AssignReadU8(
                        Logica::Types::Stream::Buffer::ReadU8Function readu8
                    );

                    /**
                     * \brief Assign an function to read an U16 inside your buffer.
                     */
                    void AssignReadU16(
                        Logica::Types::Stream::Buffer::ReadU16Function readu16
                    );

                    /**
                     * \brief Assign an function to read an U32 inside your buffer.
                     */
                    void AssignReadU32(
                        Logica::Types::Stream::Buffer::ReadU32Function readu32
                    );

                    /**
                     * \brief Assign an function to read an U64 inside your buffer.
                     */
                    void AssignReadU64(
                        Logica::Types::Stream::Buffer::ReadU64Function readu64
                    );

                    /**
                     * \brief Assign an function to read an I8 inside your buffer.
                     */
                    void AssignReadI8(
                        Logica::Types::Stream::Buffer::ReadI8Function readi8
                    );

                    /**
                     * \brief Assign an function to read an U16 inside your buffer.
                     */
                    void AssignReadI16(
                        Logica::Types::Stream::Buffer::ReadI16Function readi16
                    );

                    /**
                     * \brief Assign an function to read an I32 inside your buffer.
                     */
                    void AssignReadI32(
                        Logica::Types::Stream::Buffer::ReadI32Function readi32
                    );

                    /**
                     * \brief Assign an function to read an I64 inside your buffer.
                     */
                    void AssignReadI64(
                        Logica::Types::Stream::Buffer::ReadI64Function readi64
                    );

                    /**
                     * \brief Assign an userdata (an value that is a pointer to an object on memory
                     * that is common to all your assigned functions, like a string for example).
                     */
                    void AssignUserData(
                        void* userdata
                    );

                    /* The Buffer Functions: */

                    /**
                     * \brief Attempts to initialize your buffer, in case you called this without
                     * assigning an init function callback, the std::function will automatically
                     * crash for you to avoid any unexpected behavior.
                     */
                    void Init();
                    
                    /**
                     * \brief Attempts to set the position of your buffer.
                     */
                    void SetPosition(
                        const Logica::Types::Basic::Size position
                    );
                    
                    /**
                     * \brief Attempts to get the position of your buffer.
                     */
                    Logica::Types::Basic::Size GetPosition();
                    
                    /**
                     * \brief Attempts to close your buffer.
                     * \note KEEP IN MIND THAT THE BUFFER WON'T CALL THIS AUTOMATICALLY, IF YOU
                     * NEED TO DEALLOCATE A VALUE, YOU MUST CALL THIS FUNCTION!
                     */
                    void Close();

                    /**
                     * \brief Attempts to get an U8 from your buffer.
                     */
                    Logica::Types::Basic::U8 ReadU8();

                    /**
                     * \brief Attempts to get an U16 from your buffer.
                     */
                    Logica::Types::Basic::U16 ReadU16();
                    
                    /**
                     * \brief Attempts to get an U32 from your buffer.
                     */
                    Logica::Types::Basic::U32 ReadU32();
                    
                    /**
                     * \brief Attempts to get an U64 from your buffer.
                     */
                    Logica::Types::Basic::U64 ReadU64();
                    
                    /**
                     * \brief Attempts to get an I8 from your buffer.
                     */
                    Logica::Types::Basic::I8 ReadI8();
                    
                    /**
                     * \brief Attempts to get an I16 from your buffer.
                     */
                    Logica::Types::Basic::I16 ReadI16();
                    
                    /**
                     * \brief Attempts to get an I32 from your buffer.
                     */
                    Logica::Types::Basic::I32 ReadI32();
                    
                    /**
                     * \brief Attempts to get an I64 from your buffer.
                     */
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