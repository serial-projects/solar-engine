#include "Logica/Types/Stream/File.hpp"
#include <iostream>


/* FileUnit: */
Logica::Types::Stream::FileUnit::FileUnit()
{
    this->file      = NULL;
    this->position  = 0;
}

void Logica::Types::Stream::FileUnit::AssignFile(std::FILE* file)
{
    this->file      = file;
    this->position  = std::ftell(this->file);
}

void Logica::Types::Stream::FileUnit::CloseFile()
{
    if(this->file != NULL)
        std::fclose(this->file);
    this->file = NULL;
}

Logica::Types::Basic::Result Logica::Types::Stream::FileUnit::IsOpen()
{
    return (this->file != NULL);
}

Logica::Types::Basic::Size Logica::Types::Stream::FileUnit::GetPosition()
{
    return this->position;
}

void Logica::Types::Stream::FileUnit::SetPosition(
    const Logica::Types::Basic::Size position
)
{
    this->position = position;
    std::fseek(this->file, this->position, SEEK_SET);
}

Logica::Types::Basic::I32 Logica::Types::Stream::FileUnit::GetCharacter()
{
    Logica::Types::Basic::I32 ch = std::fgetc(this->file);
    this->position++;
    return ch;
}

/* File: */

Logica::Types::Stream::File::File()
{
    /* Assign the File variables: */
    this->unit = new Logica::Types::Stream::FileUnit;
    this->AssignUserData(static_cast<void*>(this->unit));

    /* Assign the lambdas: */
    this->AssignGetPosition(
        [](
            void* userdata
        )
        {
            Logica::Types::Stream::FileUnit* current_file_unit =
                static_cast<Logica::Types::Stream::FileUnit*>(userdata);
            return current_file_unit->GetPosition();
        }
    );
    
    this->AssignSetPosition(
        [](void* userdata, const Logica::Types::Basic::Size position)
        {
            Logica::Types::Stream::FileUnit* current_file_unit =
                static_cast<Logica::Types::Stream::FileUnit*>(userdata);
            current_file_unit->SetPosition(position);
        }
    );

    this->AssignReadI32(
        [](void* userdata)
        {
            Logica::Types::Stream::FileUnit* current_file_unit =
                static_cast<Logica::Types::Stream::FileUnit*>(userdata);
            return current_file_unit->GetCharacter();
        }
    );
}

Logica::Types::Stream::File::~File()
{
    if(this->unit->IsOpen())
        this->unit->CloseFile();
    delete this->unit;
}

void Logica::Types::Stream::File::BuildInterfaceUsingFile(
    std::FILE* file
)
{
    /* In the case the file is open, then close it and assign an new file, that way
     * we prevent possible memory leaks from happening. */
    if(this->unit->IsOpen())
        this->unit->CloseFile();
    this->unit->AssignFile(file);
}

Logica::Types::Basic::Result Logica::Types::Stream::File::SetFile(
    const Logica::Types::Basic::String& file
)
{
    Logica::Types::Basic::Result good   = true;
    std::FILE* maybe_file               = std::fopen(file.c_str(), "rb");
    if(maybe_file != NULL)
        this->BuildInterfaceUsingFile(maybe_file);
    else
        good = false;
    return good;
}

void Logica::Types::Stream::File::UnsetFile()
{
    this->unit->CloseFile();
}