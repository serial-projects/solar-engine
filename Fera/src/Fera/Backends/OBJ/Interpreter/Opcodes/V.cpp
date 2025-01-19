#include "Fera/Backends/OBJ/Interpreter/Opcodes/V.hpp"
#include "Fera/Backends/OBJ/Interpreter/Get/ArgumentVector.hpp"

void Fera::Backends::OBJ::Interpreter::Opcodes::V(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector building_index =
        Fera::Backends::OBJ::Interpreter::Get::ArgumentVector(
            instance,
            instance->properties.V_size
        );
    instance->current_V.push_back(building_index);
}