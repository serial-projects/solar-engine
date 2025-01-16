#ifndef LogicaTypesStream_hpp
#define LogicaTypesStream_hpp

#include "Logica/Types/Basic.hpp"

namespace Logica
{
    namespace Types
    {
        namespace Stream
        {
            namespace BufferFunctions
            {
                typedef void(*Init)(void* userdata);
                typedef void(*SetPosition)(void* userdata, const Logica::Types::Basic::Size position);
                typedef Logica::Types::Basic::Size(*GetPosition)(void* userdata);
                typedef Logica::Types::Basic::I32(*GetCharacter)(void* userdata);
                typedef void(*Close)(void* userdata);
            };

            /// @brief All the buffer functions & resources.
            class Buffer
            {
                private:
                    Logica::Types::Stream::BufferFunctions::Init buffer_init_f;
                    Logica::Types::Stream::BufferFunctions::SetPosition buffer_set_position_f;
                    Logica::Types::Stream::BufferFunctions::GetPosition buffer_get_position_f;
                    Logica::Types::Stream::BufferFunctions::GetCharacter buffer_get_character_f;
                    Logica::Types::Stream::BufferFunctions::Close buffer_close_f;
                    void* userdata;
                public:
                    /* initialize: */
                    Buffer();
                    ~Buffer();

                    /* Assignment Functions: */
                    virtual void AssignInit(Logica::Types::Stream::BufferFunctions::Init initf);
                    virtual void AssignSetPosition(Logica::Types::Stream::BufferFunctions::SetPosition setpf);
                    virtual void AssignGetPosition(Logica::Types::Stream::BufferFunctions::GetPosition getpf);
                    virtual void AssignGetCharacter(Logica::Types::Stream::BufferFunctions::GetCharacter getch8f);
                    virtual void AssignClose(Logica::Types::Stream::BufferFunctions::Close closef);
                    virtual void AssignUserData(void* userdata);

                    /* Buffer Functions: */
                    void Init();
                    void SetPosition(const Logica::Types::Basic::Size position);
                    Logica::Types::Basic::Size GetPosition();
                    Logica::Types::Basic::I32 GetCharacter();
                    void Close();
            };

            /* TODO: this implementation is NOT completely safe! */
            /* TODO: use buffer for avoid calling the system multiple times. */
            
            /// @brief Handles automatically files instead of loading everything to memory at once.
            struct FileHandler
            {
                std::FILE* f_instance;
                Logica::Types::Basic::Size position;
                FileHandler();
            };

            class FileBuffer : public Logica::Types::Stream::Buffer
            {
                private:
                    Logica::Types::Stream::FileHandler current_file_handler;
                public:
                    FileBuffer();
                    ~FileBuffer();
                    Logica::Types::Basic::Result SetFile(const Logica::Types::Basic::String& path);
            };
        };
    };
};

#endif