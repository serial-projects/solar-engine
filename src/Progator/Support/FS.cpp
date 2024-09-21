#include "Progator/Support/FS.hpp"

#include <cstdio>
#include <cstdlib>

Progator::Support::FileBuffer Progator::Support::FileBufferGet(const Progator::Character* path)
{
    std::FILE *file_pointer = std::fopen(path, "r");
    Progator::Support::FileBuffer buffer = nullptr;
    if(file_pointer != nullptr)
    {
        std::fseek(file_pointer, 0, SEEK_END);
        Progator::U32 length = std::ftell(file_pointer);
        buffer = new Progator::Character[length + 1];
        
        std::fseek(file_pointer, 0, SEEK_SET);
        auto _A = std::fread(buffer, length, sizeof(Progator::Character), file_pointer);
        
        std::fclose(file_pointer);
        buffer[length] = 0;
    }
    return buffer;
}

void Progator::Support::FileBufferDestroy(Progator::Support::FileBuffer buffer)
{
    delete buffer;
}