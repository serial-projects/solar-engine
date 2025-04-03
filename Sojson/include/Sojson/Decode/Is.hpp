#ifndef SojsonDecodeIs_hpp
#define SojsonDecodeIs_hpp

#include "Sojson/Types.hpp"

namespace Sojson
{
    namespace Decode
    {
        namespace Is
        {
            enum Types
            {
                Nothing     = 0,
                Integer,
                Decimal,
                String,
                Boolean,
                Null
            };
            Sojson::Decode::Is::Types TokenType(const Sojson::Types::Basic::String& key);
        };
    };
};

#endif