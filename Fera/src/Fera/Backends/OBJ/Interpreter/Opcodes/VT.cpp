#include "Fera/Backends/OBJ/Interpreter/Opcodes/VT.hpp"
#include "Fera/Backends/OBJ/Interpreter/Get/ArgumentVector.hpp"

void Fera::Backends::OBJ::Interpreter::Opcodes::VT(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector building_index =
        Fera::Backends::OBJ::Interpreter::Get::ArgumentVector(
            instance,
            instance->properties.VT_size
        );
    instance->current_VT.push_back(building_index);
}