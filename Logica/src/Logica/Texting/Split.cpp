#include "Logica/Texting/Split.hpp"

inline Logica::Texting::SplitResult Logica::Texting::Split(
    Logica::Types::Basic::String& source,
    Logica::Types::Basic::CH8 separator
)
{
    Logica::Texting::SplitResult split_result;
    Logica::Types::Basic::String accumulator;
    for(auto content : source)
    {
        if(content == separator)
        {
            split_result.push_back(accumulator);
            accumulator.clear();
        }
        else
            accumulator.push_back(content);
    }
    split_result.push_back(accumulator);
    return split_result;
}