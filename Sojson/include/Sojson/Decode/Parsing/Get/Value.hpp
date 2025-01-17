#ifndef SojsonDecodeGetValue_hpp
#define SojsonDecodeGetValue_hpp

#include "Sojson/Node.hpp"
#include "Sojson/Decode/Instance.hpp"

namespace Sojson
{
    namespace Decode
    {
        namespace Parsing
        {
            namespace Get
            {
                Sojson::Node* Value(
                    Sojson::Decode::Instance* instance,
                    const Sojson::Types::String token,
                    const Sojson::Types::U8 depth
                );
                Sojson::Node* ValueRoot(
                    Sojson::Decode::Instance* instance
                );
            };
        };
    };
};

#endif