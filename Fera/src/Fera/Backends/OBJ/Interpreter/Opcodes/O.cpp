#include "Fera/Backends/OBJ/Interpreter/Opcodes/O.hpp"
void Fera::Backends::OBJ::Interpreter::Opcodes::O(
    Fera::Backends::OBJ::Interpreter::Instance *instance
)
{
    /* NOTE: when O is set, then we do the same as on G, dump the buffer and
     * proceed to change the current object/tree element.
     */

    /* TODO: check for EOF here. */
    Logica::Types::Basic::String current_token =
        instance->tokenizer.GetToken(false);
    
    /* Generate the object + dump the buffer on the node! */
    Fera::Backends::OBJ::Interpreter::InstanceGenerateObject(instance);
    instance->working_object.clear();

    /* Assign the new object: */
    instance->current_object = current_token;
}