#include "Logica/Types/Buffer/File.hpp"
#include "Logica/Data/File.hpp"

Logica::Types::Buffer::File::File()
{
    this->current_handler = Logica::Types::Buffer::File::Handler();
    this->AssignUserData(static_cast<void*>(&this->current_handler));
    this->AssignInitCallback(
        [](void* userdata)
        {
            Logica::Types::Buffer::File::Handler* current_handler =
                static_cast<Logica::Types::Buffer::File::Handler*>(userdata);
            /* NOTE: Here we also account for when the file is being reloaded or changed. */
            if(current_handler->os_connector != NULL)
                fclose(current_handler->os_connector);
            current_handler->os_connector   = fopen(current_handler->path.c_str(), "rb");
            current_handler->position       = 0;
        }
    );
    this->AssignSetPositionCallback(
        [](void* userdata, const Logica::Types::Basic::Size position)
        {
            Logica::Types::Buffer::File::Handler* current_handler =
                static_cast<Logica::Types::Buffer::File::Handler*>(userdata);
            current_handler->position = position;
            fseek(current_handler->os_connector, position, SEEK_SET);
        }
    );
    this->AssignGetPositionCallback(
        [](void* userdata)
        {
            Logica::Types::Buffer::File::Handler* current_handler =
                static_cast<Logica::Types::Buffer::File::Handler*>(userdata);
            return current_handler->position;
        }
    );
    this->AssignGetCharacterCallback(
        [](void* userdata)
        {
            Logica::Types::Buffer::File::Handler* current_handler =
                static_cast<Logica::Types::Buffer::File::Handler*>(userdata);
            Logica::Types::Basic::I32 value = fgetc(current_handler->os_connector);
            current_handler->position++;
            return value;
        }
    );
    this->AssignCloseCallback(
        [](void* userdata)
        {
            Logica::Types::Buffer::File::Handler* current_handler =
                static_cast<Logica::Types::Buffer::File::Handler*>(userdata);
            fclose(current_handler->os_connector);
            current_handler->os_connector = nullptr;
        }
    );
}

Logica::Types::Buffer::File::~File()
{
    /* TODO: on the future, remove this since this function does nothing. */
}

Logica::Types::Basic::Result Logica::Types::Buffer::File::SetFile(
    const Logica::Types::Basic::String& path
)
{
    Logica::Types::Basic::Result file_exists = Logica::Data::File::Exists(path);
    if(file_exists)
        this->current_handler.path = path;
    return file_exists;
}