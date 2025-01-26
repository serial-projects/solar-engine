#ifndef ProgatorTypesSpecificsMesh_hpp
#define ProgatorTypesSpecificsMesh_hpp

#include "Progator/Types/Basic.hpp"

namespace Progator
{
    namespace Types
    {
        namespace Specifics
        {
            namespace Mesh
            {
                /* TODO: this supports 0 - 255 values; */

                /// @brief The layout an mesh can have.
                struct Layout
                {
                    /// @brief The identity of the layout.
                    Progator::Types::Basic::U8 id;

                    /// @brief Size of all the entire layout.
                    Progator::Types::Basic::U8 size;
                    
                    /// @brief You want this to be the result of the stride for an layout, like:
                    /// instead of sizeof(float), use stride_size = sizeof(float) & stride =
                    /// stride_size * stride (or 3 x 3 (for an vec3 for example) ...)
                    Progator::Types::Basic::U8 stride_size;

                    /// @brief the amount of values on the current layout.
                    Progator::Types::Basic::U8 stride;

                    /// @brief To the pointer calculation, the amount of padding.
                    Progator::Types::Basic::U8 padding;
                };
            };
        };
    };
};

#endif