#include "Fera/Backends/OBJ/Interpreter/Opcodes/S.hpp"

void Fera::Backends::OBJ::Interpreter::Opcodes::S(
    Fera::Backends::OBJ::Interpreter::Instance *instance
)
{
    /* NOTE: s opcode is not interpreted since Solar Engine itself doesn't really need it to render
     * anything, any mesh modification or material property is done on the manifest itself rather
     * than the OBJ file or whatever file it is.
     */
    return;
}