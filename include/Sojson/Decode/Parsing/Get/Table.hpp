#ifndef SojsonDecodeGetTable_hpp
#define SojsonDecodeGetTable_hpp

#include "Sojson/Decode/Parsing/Get/Value.hpp"

namespace Sojson
{
    namespace Decode
    {
        namespace Parsing 
        {
            namespace Get
            {
                Sojson::Node* Table(
                    Sojson::Decode::Instance* instance,
                    const Sojson::Types::U8 current_depth
                );
            };
        };
    };
};

#endif