#include "Logica/Data/String.hpp"

/* SPLIT FUNCTIONS: */

template <typename IndexVariableType, IndexVariableType IndexVariableLimit>
Logica::Data::String::SplitResult Logica::Data::String::SplitBase(
    const Logica::Types::Basic::String& e,
    const Logica::Types::Basic::CH8 delimiter
)
{
    Logica::Data::String::SplitResult result;
    Logica::Types::Basic::String accumulator;
    for(IndexVariableType index = 0; index < e.size() && index < IndexVariableLimit; ++index)
    {
        const Logica::Types::Basic::CH8 character = e.at(index);
        if(character == delimiter)
        {
            if(accumulator.size() > 0)
            {
                result.push_back(accumulator);
                accumulator.clear();
            }
        }
        else accumulator.push_back(character);
    }
    if(accumulator.size() > 0)
        result.push_back(accumulator);
    return result;
}

template Logica::Data::String::SplitResult
    Logica::Data::String::SplitBase<Logica::Types::Basic::U8, UINT8_MAX>
    (const Logica::Types::Basic::String& e, const Logica::Types::Basic::CH8 delimiter);

template Logica::Data::String::SplitResult
    Logica::Data::String::SplitBase<Logica::Types::Basic::U16, UINT16_MAX>
    (const Logica::Types::Basic::String& e, const Logica::Types::Basic::CH8 delimiter);

template Logica::Data::String::SplitResult
    Logica::Data::String::SplitBase<Logica::Types::Basic::U32, UINT32_MAX>
    (const Logica::Types::Basic::String& e, const Logica::Types::Basic::CH8 delimiter);

template Logica::Data::String::SplitResult
    Logica::Data::String::SplitBase<Logica::Types::Basic::U64, UINT64_MAX>
    (const Logica::Types::Basic::String& e, const Logica::Types::Basic::CH8 delimiter);

Logica::Data::String::SplitResult Logica::Data::String::Split(
    const Logica::Types::Basic::String& e,
    const Logica::Types::Basic::CH8 delimiter
)
{
    return Logica::Data::String::SplitBase<Logica::Types::Basic::U16,UINT16_MAX>(e, delimiter);
}