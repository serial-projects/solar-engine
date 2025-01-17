#ifndef FeraBackendsOBJDecode_hpp
#define FeraBackendsOBJDecode_hpp

#include "Fera/Backends/OBJ/Interpreter.hpp"

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            Fera::Backends::OBJ::Interpreter::Instance Load(Logica::Types::Stream::Buffer* buffer);
            Fera::Meshing::Mesh* Parse(Fera::Backends::OBJ::Interpreter::Instance* instance);
        };
    };
};

#endif