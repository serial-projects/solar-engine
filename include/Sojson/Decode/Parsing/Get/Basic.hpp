#ifndef SojsonDecodeParsingGetBasic_hpp
#define SojsonDecodeParsingGetBasic_hpp

#include "Sojson/Decode/Instance.hpp"
#include "Sojson/Node.hpp"

namespace Sojson
{
    namespace Decode
    {
        namespace Parsing
        {
            namespace Get
            {
                Sojson::Node* BasicValueFromToken(
                    Sojson::Decode::Instance* instance,
                    const Logica::Types::Basic::String& token
                );
            };
        };
    };
};

#endif