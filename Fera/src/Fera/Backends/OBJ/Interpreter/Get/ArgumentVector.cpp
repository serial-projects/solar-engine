#include "Fera/Backends/OBJ/Interpreter/Get/ArgumentVector.hpp"
#include "Fera/Backends/OBJ/Interpreter/Get/TokenTypes.hpp"

Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector 
    Fera::Backends::OBJ::Interpreter::Get::ArgumentVector(
        Fera::Backends::OBJ::Interpreter::Instance *instance,
        const Fera::Types::U8 v_size
    )
{
    Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector building_index;
    for(Fera::Types::U8 index=0; index < v_size && index < UINT8_MAX; ++index)
    {
        Logica::Types::Basic::String current_token = instance->tokenizer.GetToken(false);
        
        /* NOTE: expected parameter but buffer ended... */
        if(instance->tokenizer.GetState() != Logica::Texting::Tokenizer::Instance::States::RUNNING)
        {
            instance->state = Fera::Backends::OBJ::Interpreter::InstanceStates::Died;
            instance->validator.SetError(
                Fera::Backends::OBJ::Interpreter::InstanceErrors::EarlyEnd,
                "at line: %d, on opcode V, expected number/decimal but got EOF",
                instance->tokenizer.GetCurrentLine()
            );
            break;
        }

        /* check for what type we got, here we accept only number/decimal! */
        Fera::Types::U8 current_token_type = 
            Fera::Backends::OBJ::Interpreter::Get::TokenType(current_token);
        if(
            (current_token_type != Fera::Backends::OBJ::Interpreter::Get::TokenTypes::Decimal) &&
            (current_token_type != Fera::Backends::OBJ::Interpreter::Get::TokenTypes::Number)
        )
        {
            instance->state = Fera::Backends::OBJ::Interpreter::InstanceStates::Died;
            instance->validator.SetError(
                Fera::Backends::OBJ::Interpreter::InstanceErrors::EarlyEnd,
                "at line: %d, on opcode V, expected number/decimal but got token = %s",
                instance->tokenizer.GetCurrentLine(),
                current_token.c_str()
            );
            break;
        }

        /* NOTE: even if the token is a integer or number, transform it to F32 since it is our
         * main representation method here.
         */
        Fera::Types::F32 point = std::stof(current_token);
        building_index.push_back(point);
    }
    return building_index;
}