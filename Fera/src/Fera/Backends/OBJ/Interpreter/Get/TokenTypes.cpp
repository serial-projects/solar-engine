#include "Fera/Backends/OBJ/Interpreter/Get/TokenTypes.hpp"

Fera::Types::U8 Fera::Backends::OBJ::Interpreter::Get::TokenType(
    Fera::Types::String &token
)
{
    Fera::Types::U8 type = Fera::Backends::OBJ::Interpreter::Get::TokenTypes::Nothing;

    /* strings require : "" -> 2 characters */
    if(token.size() >= 2)
    {
        Fera::Types::CH8 lt = token.at(0);
        Fera::Types::CH8 rt = token.at(token.size() - 1);
        if((lt == '"' || lt == '\'') && (lt == rt))
        {
            type = Fera::Backends::OBJ::Interpreter::Get::TokenTypes::String;
            goto skip_due_token_being_string;
        }
    }
    
    /* If the program came to here, we assume it is a number so we can parse it ok ;-) */
    type = Fera::Backends::OBJ::Interpreter::Get::TokenTypes::Number;
    for(Fera::Types::U16 index = 0; index < token.size() && index < UINT16_MAX; ++index)
    {
        Fera::Types::CH8 current_token = token.at(index);
        if((current_token >= '0' && current_token <= '9'))
            continue;
        else
        {
            if(current_token == '-' && index == 0)
                continue;
            else if(
                current_token == '.' && 
                type == Fera::Backends::OBJ::Interpreter::Get::TokenTypes::Number
            )
            {
                type = Fera::Backends::OBJ::Interpreter::Get::TokenTypes::Decimal;
                continue;
            }
            else
            {
                /* Whatever type is this, LOL. */
                type = Fera::Backends::OBJ::Interpreter::Get::TokenTypes::Unknown;
                break;
            }
        }
    }

    skip_due_token_being_string:
    return type;
}