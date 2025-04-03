#include "Sojson/Decode/Is.hpp"

Sojson::Decode::Is::Types Sojson::Decode::Is::TokenType(
    const Sojson::Types::Basic::String& key
)
{
    Sojson::Decode::Is::Types type = Sojson::Decode::Is::Nothing;
    
    /* In case of an empty character then we return Nothing. */
    if(key.size() <= 0)
        goto skip_parsing;
    
    /* Here we look for more special types: */
    if(key.size() >= 2)
    {
        Sojson::Types::Basic::CH8 lv = key.at(0);
        Sojson::Types::Basic::CH8 rv = key.at(key.size() - 1);
        
        /* For String: */
        if((lv == '\"' || lv == '\'') && (lv == rv))
        {
            type = Sojson::Decode::Is::String;
            goto skip_parsing;
        }

        /* For boolean: */
        if(key == "yes" || key == "true" || key == "false" || key == "no")
        {
            type = Sojson::Decode::Is::Boolean;
            goto skip_parsing;
        }

        /* For Null: */
        if(key == "null")
        {
            type = Sojson::Decode::Is::Null;
            goto skip_parsing;
        }
    }

    /* Parse Integer:
     * TODO: implement 0xn notation;
     * TODO: implement 0bn notation;
     */
    type = Sojson::Decode::Is::Integer;
    for(
        Sojson::Types::Basic::U16 index = 0;
        (index < key.size() && index < UINT16_MAX);
        index++
    )
    {
        Sojson::Types::Basic::CH8 ct = key.at(index);
        if((ct >= '0' && ct <= '9'))
            continue;
        else
        {
            if((ct == '-' && index == 0))
                continue;
            else if((ct == '.') && (type == Sojson::Decode::Is::Integer))
            {
                type = Sojson::Decode::Is::Decimal;
                continue;
            }
            else
            {
                type = Sojson::Decode::Is::Nothing;
                break;
            }
        }
        /* DONE: */
    }
skip_parsing:
    return type;
}