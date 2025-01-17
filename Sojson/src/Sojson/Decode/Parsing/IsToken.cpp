#include "Sojson/Decode/Parsing/IsToken.hpp"

/* TODO: support 0x or 0b notation! */
const Sojson::Types::U8 Sojson::Decode::Parsing::IsToken::Type(
    const Sojson::Types::String& token
)
{
    /* Assume we are working the number: */
    Sojson::Types::U8 type =
        Sojson::Decode::Parsing::IsToken::TypeResult::Number;
    
    /* NOTE: test for the possible "" token, that has nothing. */
    if(token.size() <= 0)
    {
        type = Sojson::Decode::Parsing::IsToken::TypeResult::Neither;
        goto skip_number_parsing;
    }

    /* BEFORE parsing to numbers, adiantum this: string && booleans: */
    if(token.size() >= 2)
    {
        Sojson::Types::CH8 lv = token.at(0);
        Sojson::Types::CH8 rv = token.at(token.size() - 1);
        
        if((lv == '"' || lv == '\'') && (lv == rv))
        {
            type = Sojson::Decode::Parsing::IsToken::TypeResult::String;
            goto skip_number_parsing;
        }
        
        if(token == "yes" || token == "true" || token == "false" || token == "no")
        {
            type = Sojson::Decode::Parsing::IsToken::TypeResult::Boolean;
            goto skip_number_parsing;
        }

        if(token == "null")
        {
            type = Sojson::Decode::Parsing::IsToken::TypeResult::Null;
            goto skip_number_parsing;
        }
    }

    /* If anything then parse for the numbers, if the token is invalid, for example: AOE, it will
     * not pass from this stage anyway. 
     */
    for(Sojson::Types::U16 index = 0; index < token.size() && index < UINT16_MAX; ++index)
    {
        Sojson::Types::CH8 current_token = token.at(index);
        if((current_token >= '0' && current_token <= '9'))
            continue;
        else
        {
            if(current_token == '-' && index == 0)
                continue;
            else if(
                current_token == '.' && 
                type == Sojson::Decode::Parsing::IsToken::TypeResult::Number
            )
            {
                type = Sojson::Decode::Parsing::IsToken::TypeResult::Decimal;
                continue;
            }
            else
            {
                /* IF no '-' at the start or multiple dots or letters or whatever, then break
                 * and set to neither result. */
                type = Sojson::Decode::Parsing::IsToken::TypeResult::Neither;
                break;
            }
        }
    }
    skip_number_parsing:
    return type;
}

const Sojson::Types::Result Sojson::Decode::Parsing::IsToken::ValidKey(
    const Sojson::Types::String& token
)
{
    Sojson::Types::Result valid = false;
    if(token.size() >= 2)
    {
        const Sojson::Types::CH8 lv = token.at(0);
        const Sojson::Types::CH8 rv = token.at(token.size() - 1);
        valid = ((lv == '\"') && (lv == rv));
    }
    return valid;
}