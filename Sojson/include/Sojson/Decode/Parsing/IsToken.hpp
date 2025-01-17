#ifndef SojsonDecodeParsingIsToken_hpp
#define SojsonDecodeParsingIsToken_hpp

#include "Sojson/Types.hpp"

namespace Sojson
{
    namespace Decode
    {
        namespace Parsing
        {
            /// @brief Some functions to test for the token properties:
            namespace IsToken
            {
                namespace TypeResult
                {
                    enum NumberOrDecimalResult
                    {
                        Neither = 0,
                        Number,
                        Decimal,
                        String,
                        Boolean,
                        Null
                    };
                };
                const Sojson::Types::U8 Type(const Sojson::Types::String& token);
                const Sojson::Types::Result ValidKey(const Sojson::Types::String& token);
            };
        };
    };
};

#endif