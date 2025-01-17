#ifndef FeraTypes_hpp
#define FeraTypes_hpp

/* NOTE: Fera is built on Logica and so its all Solar RPG Engine Project. */
#include "Logica/Logica.hpp"

namespace Fera
{
    namespace Types 
    {
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

        /* Decimal: */
        
        typedef Logica::Types::Basic::F32   F32;
        typedef Logica::Types::Basic::F64   F64;

        /* Yes or No: */
        
        typedef Logica::Types::Basic::Boolean Boolean;
        typedef Logica::Types::Basic::Result Result;

        /* String: */
        
        typedef Logica::Types::Basic::String String;

        /// @brief templates for certain types.
        namespace Prototyping
        {
            template <typename XType, typename YType>
            struct Vector2
            {
                XType x;
                YType y;
            };
            template <typename XType, typename YType, typename ZType>
            struct Vector3
            {
                XType x;
                YType y;
                ZType z;
            };
        };

        /// @brief Contains various types of vectors to store data.
        namespace Vec2
        {
            typedef Fera::Types::Prototyping::Vector2<Fera::Types::F32, Fera::Types::F32> F32;
            typedef Fera::Types::Prototyping::Vector2<Fera::Types::I32, Fera::Types::I32> I32;
        };

        /// @brief Contains various types of vectors to store data.
        namespace Vec3
        {
            typedef Fera::Types::Prototyping::Vector3<Fera::Types::F32, Fera::Types::F32, Fera::Types::F32> F32;
            typedef Fera::Types::Prototyping::Vector3<Fera::Types::I32, Fera::Types::I32, Fera::Types::F32> I32;
        };
    };
};

#endif