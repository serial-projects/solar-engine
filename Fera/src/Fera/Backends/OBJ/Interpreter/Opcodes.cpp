#include "Fera/Backends/OBJ/Interpreter/Opcodes.hpp"

void Fera::Backends::OBJ::Interpreter::InstancePerformOpcode(
    Fera::Backends::OBJ::Interpreter::Instance* instance,
    const Fera::Types::String& opcode
)
{
    if(
        Fera::Backends::OBJ::Interpreter::OpcodeTable.find(opcode) !=
        Fera::Backends::OBJ::Interpreter::OpcodeTable.end()
    )
    {
        Fera::Backends::OBJ::Interpreter::OpcodeFunction wrap = 
            Fera::Backends::OBJ::Interpreter::OpcodeTable.at(opcode);
        wrap(instance);
    }
    else
    {
        instance->state = Fera::Backends::OBJ::Interpreter::InstanceStates::Died;
        instance->validator.SetError(
            Fera::Backends::OBJ::Interpreter::InstanceErrors::InvalidOpcode,
            "at line %d, found an invalid opcode = %s",
            instance->tokenizer.GetCurrentLine(),
            opcode.c_str()
        );
    }
}