#ifndef SojsonTypesBasic_hpp
#define SojsonTypesBasic_hpp

#include "Logica/Logica.hpp"
#include <string>
#include <vector>

namespace Sojson
{
    namespace Types
    {
        namespace Basic
        {
            typedef Logica::Types::Basic::U8        U8;
            typedef Logica::Types::Basic::I8        I8;
            typedef Logica::Types::Basic::U16       U16;
            typedef Logica::Types::Basic::I16       I16;
            typedef Logica::Types::Basic::U32       U32;
            typedef Logica::Types::Basic::I32       I32;
            typedef Logica::Types::Basic::U64       U64;
            typedef Logica::Types::Basic::I64       I64;
            typedef Logica::Types::Basic::F32       F32;
            typedef Logica::Types::Basic::F64       F64;
            typedef Logica::Types::Basic::CH8       CH8;
            typedef Logica::Types::Basic::Result    Result;
            typedef Logica::Types::Basic::String    String;
        };
    };
};

#endif