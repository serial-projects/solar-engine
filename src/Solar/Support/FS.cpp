#include "Solar/Support/FS.hpp"
#include "Progator/Support/FS.hpp"

#include <cstdio>

bool Solar::Support::DoesFileExist(const Solar::Character* path)
{
    std::FILE *fileptr = std::fopen(path, "r");
    if(fileptr == NULL) return false;
    else
    {
        std::fclose(fileptr);
        return true;
    }
}

/* HACK: Solar::Support::LoadFile(): just uses Progator::Support::
 * */
Solar::String Solar::Support::LoadFile(const Solar::Character* path)
{
    Progator::Support::FileBuffer buffer = Progator::Support::FileBufferGet(path);
    Solar::String converted_buffer = Solar::String(buffer);
    Progator::Support::FileBufferDestroy(buffer);

    /* NOTE: return the buffer: */
    return converted_buffer;
}