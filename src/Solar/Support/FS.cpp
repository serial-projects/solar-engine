#include "Solar/Support/FS.hpp"
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