#include "Fera/Backends/OBJ/Interpreter/Opcodes/VN.hpp"
#include "Fera/Backends/OBJ/Interpreter/Get/ArgumentVector.hpp"

void Fera::Backends::OBJ::Interpreter::Opcodes::VN(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector building_index =
        Fera::Backends::OBJ::Interpreter::Get::ArgumentVector(
            instance,
            instance->properties.VN_size
        );
    instance->current_VN.push_back(building_index);
}