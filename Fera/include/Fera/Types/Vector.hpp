#ifndef FeraTypesVector_hpp
#define FeraTypesVector_hpp

#include "Fera/Types/Basic.hpp"

namespace Fera
{
    namespace Types
    {
        /**
         * \brief When naming the Vectors, mind the specification: Vector2 made of F32 is: F32x2,
         * An Vector3 made of I32 is I32x3.
         */
        namespace Vector
        {
            /**
             * \brief Base2D is a common base for 2D vectors.
             */
            template <typename T>
            class Base2D
            {
                public:
                    T   x = 0;
                    T   y = 0;
            };

            /**
             * \brief An Vector2 made of F32.
             */
            typedef Fera::Types::Vector::Base2D<Fera::Types::Basic::F32> F32x2;

            /**
             * \brief An Vector2 made of I32.
             */
            typedef Fera::Types::Vector::Base2D<Fera::Types::Basic::I32> I32x2;

            /**
             * \brief Base3D is a common base for 3D vectors.
             */
            template <typename T>
            class Base3D
            {
                public:
                    T   x = 0;
                    T   y = 0;
                    T   z = 0;
            };

            /**
             * \brief An Vector3 made of F32.
             */
            typedef Fera::Types::Vector::Base3D<Fera::Types::Basic::F32> F32x3;

            /**
             * \brief An Vector3 made of I32.
             */
            typedef Fera::Types::Vector::Base3D<Fera::Types::Basic::I32> I32x3;
        };
    };
};

#endif