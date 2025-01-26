#include "Logica/Data/File.hpp"

/* Cat Functionality: */
#include <fstream>
#include <sstream>

Logica::Types::Basic::String Logica::Data::File::Cat(const Logica::Types::Basic::String &file)
{
    std::ifstream fp;
    fp.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fp.open(file);
    
    /* do sstream operations here: */
    std::stringstream fp_stream;
    fp_stream << fp.rdbuf();
    fp.close();

    /* finally: */
    return fp_stream.str();
}

Logica::Types::Basic::Result Logica::Data::File::Exists(const Logica::Types::Basic::String &file)
{
    Logica::Types::Basic::Result exists = true;
    std::FILE *fp = std::fopen(file.c_str(), "r");
    if(fp == NULL)
        exists = false;
    else
        std::fclose(fp);
    return exists;
}
