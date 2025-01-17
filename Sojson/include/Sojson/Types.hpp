#ifndef SojsonTypes_hpp
#define SojsonTypes_hpp

// Include the Logica Types here and all the Logica Infraestructure.
#include "Logica/Logica.hpp"

// Sojson Includes:
#include "Sojson/Config.hpp"

namespace Sojson
{
    namespace Types {
        /* Integers: */
        typedef Logica::Types::Basic::U8    U8;
        typedef Logica::Types::Basic::I8    I8;
        typedef Logica::Types::Basic::U16   U16;
        typedef Logica::Types::Basic::I16   I16;
        typedef Logica::Types::Basic::U32   U32;
        typedef Logica::Types::Basic::I32   I32;
        typedef Logica::Types::Basic::U64   U64;
        typedef Logica::Types::Basic::I64   I64;
        typedef Logica::Types::Basic::CH8   CH8;

        /* Yes or No: */
        typedef Logica::Types::Basic::Boolean Boolean;
        typedef Logica::Types::Basic::Result Result;

        /* String: */
        typedef Logica::Types::Basic::String String;
    };
};

#endif