#include "Logica/Types/Stream.hpp"
#include <iostream>

/* initialize: */
Logica::Types::Stream::Buffer::Buffer()
{
    std::cout
        << __PRETTY_FUNCTION__
        << ": DONE.\n";
    this->buffer_init_f = nullptr;
    this->buffer_set_position_f = nullptr;
    this->buffer_get_position_f = nullptr;
    this->buffer_get_character_f = nullptr;
    this->buffer_close_f = nullptr;
    this->userdata = nullptr;
}

Logica::Types::Stream::Buffer::~Buffer()
{
    /* NOTE: do nothing, this function should be put on the STACK! */
}

/* Assignment Functions: */
void Logica::Types::Stream::Buffer::AssignInit(
    Logica::Types::Stream::BufferFunctions::Init initf
)
{
    this->buffer_init_f = initf;
}

void Logica::Types::Stream::Buffer::AssignSetPosition(
    Logica::Types::Stream::BufferFunctions::SetPosition setpf
)
{
    this->buffer_set_position_f = setpf;
}

void Logica::Types::Stream::Buffer::AssignGetPosition(
    Logica::Types::Stream::BufferFunctions::GetPosition getpf
)
{
    this->buffer_get_position_f = getpf;
}

void Logica::Types::Stream::Buffer::AssignGetCharacter(
    Logica::Types::Stream::BufferFunctions::GetCharacter getch8f
)
{
    this->buffer_get_character_f = getch8f;
}

void Logica::Types::Stream::Buffer::AssignClose(
    Logica::Types::Stream::BufferFunctions::Close closef
)
{
    this->buffer_close_f = closef;
}

void Logica::Types::Stream::Buffer::AssignUserData(
    void* userdata
)
{
    this->userdata = userdata;
}

/* Buffer Functions: */
void Logica::Types::Stream::Buffer::Init()
{
    if(this->buffer_init_f != nullptr)
        this->buffer_init_f(this->userdata);
}

void Logica::Types::Stream::Buffer::SetPosition(
    const Logica::Types::Basic::Size position
)
{
    if(this->buffer_set_position_f != nullptr)
        this->buffer_set_position_f(this->userdata, position);
}

Logica::Types::Basic::Size Logica::Types::Stream::Buffer::GetPosition()
{
    Logica::Types::Basic::Size size = 0;
    if(this->buffer_get_position_f != nullptr)
        size = this->buffer_get_position_f(this->userdata);
    return size;
}

Logica::Types::Basic::I32 Logica::Types::Stream::Buffer::GetCharacter()
{
    Logica::Types::Basic::CH8 ch = 0;
    if(this->buffer_get_character_f != nullptr)
        ch = this->buffer_get_character_f(this->userdata);
    return ch;
}

void Logica::Types::Stream::Buffer::Close()
{
    if(this->buffer_close_f != nullptr)
        this->buffer_close_f(this->userdata);
}

/* FileBuffer: */
Logica::Types::Stream::FileBuffer::FileBuffer()
{
    /* DONE: */
    std::cout
        << __PRETTY_FUNCTION__
        << ": DONE.\n";
}

Logica::Types::Stream::FileBuffer::~FileBuffer()
{
    /* DO NOTHING as everything is on the stack. */
    return;
}

static void __LogicaTypesStreamFileBufferInitGenericFunction(
    void* userdata
)
{
    /* NOTE: get the current position: */
    ((Logica::Types::Stream::FileHandler*)(userdata))->position = 
        ftell( ((Logica::Types::Stream::FileHandler*)(userdata))->f_instance );
    return;
}

static void __LogicaTypesStreamFileBufferSetPositionGenericFunction(
    void* userdata, 
    const Logica::Types::Basic::Size position
)
{
    fseek(
        ((Logica::Types::Stream::FileHandler*)(userdata))->f_instance,
        position,
        SEEK_SET
    );
    ((Logica::Types::Stream::FileHandler*)(userdata))->position = position;
}

static Logica::Types::Basic::Size __LogicaTypesStreamFileBufferGetPositionGenericFunction(
    void *userdata
)
{
    return ((Logica::Types::Stream::FileHandler*)(userdata))->position;
}

static Logica::Types::Basic::I32 __LogicaTypesStreamFileBufferGetCharacterGenericFunction(
    void* userdata
)
{
    Logica::Types::Basic::I32 ch = fgetc(
        ((Logica::Types::Stream::FileHandler*)(userdata))->f_instance
    );
    ((Logica::Types::Stream::FileHandler*)(userdata))->position++;
    return ch;
}

static void __LogicaTypesStreamFileBufferCloseGenericFunction(
    void* userdata
)
{
    fclose(((Logica::Types::Stream::FileHandler*)(userdata))->f_instance);
}

Logica::Types::Stream::FileHandler::FileHandler()
{
    this->f_instance = nullptr;
    this->position = 0;
}

Logica::Types::Basic::Result Logica::Types::Stream::FileBuffer::SetFile(
    const Logica::Types::Basic::String& path
)
{
    /* NOTE: unless everything is loaded, this code is false. */
    Logica::Types::Basic::Result result = false;

    /* Factory: Build some functions to handle this on the FILE stream we
     * open, we are using the C since it is faster. */
    this->current_file_handler.f_instance = std::fopen(path.c_str(), "rb");
    if(this->current_file_handler.f_instance == nullptr)
        goto skip_everything;
    this->AssignUserData((void*)&this->current_file_handler);
    this->AssignInit(__LogicaTypesStreamFileBufferInitGenericFunction);
    this->AssignSetPosition(__LogicaTypesStreamFileBufferSetPositionGenericFunction);
    this->AssignGetPosition(__LogicaTypesStreamFileBufferGetPositionGenericFunction);
    this->AssignGetCharacter(__LogicaTypesStreamFileBufferGetCharacterGenericFunction);
    this->AssignClose(__LogicaTypesStreamFileBufferCloseGenericFunction);
    result = true;
skip_everything:
    return result;
}