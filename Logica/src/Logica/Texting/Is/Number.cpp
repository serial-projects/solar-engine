#include "Logica/Texting/Is/Number.hpp"

Logica::Types::Basic::Result Logica::Texting::Is::Number(
    const Logica::Types::Basic::String &token,
    const Logica::Types::Basic::Boolean accept_negatives
)
{
    Logica::Types::Basic::Result is_number = true;
    for(Logica::Types::Basic::U16 index=0; index < token.size() && index < UINT16_MAX; ++index)
    {
        Logica::Types::Basic::CH8 current_character = token.at(index);
        if((current_character>='0' && current_character <= '9'))
            continue;
        else if(accept_negatives && ((current_character=='-') && index == 0))
            continue;
        else    
        {
            is_number = false;
            break;
        }
    }
    return is_number;
}