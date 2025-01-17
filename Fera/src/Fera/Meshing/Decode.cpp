#include "Fera/Backends/OBJ/Decode.hpp"

Fera::Backends::OBJ::Interpreter::Instance Fera::Backends::OBJ::Load(
    Logica::Types::Stream::Buffer* buffer
)
{
    Fera::Backends::OBJ::Interpreter::Instance instance = 
        Fera::Backends::OBJ::Interpreter::InstanceNew();
    Fera::Backends::OBJ::Interpreter::InstanceInit(&instance, buffer);
    return instance;
}

Fera::Meshing::Mesh* Fera::Backends::OBJ::Parse(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    Fera::Backends::OBJ::Interpreter::InstanceParse(instance);
    return instance->root;
}