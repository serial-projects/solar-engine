#ifndef ProgatorTypesSpecificsRenderer_hpp
#define ProgatorTypesSpecificsRenderer_hpp

#include "Progator/Types/Basic.hpp"

namespace Progator
{
    namespace Types
    {
        namespace Specifics
        {
            namespace Renderer
            {
                /// @brief size for the renderer.
                typedef Progator::Types::Basic::U16 Size;

                /// @brief position for the renderer.
                typedef Progator::Types::Basic::U16 Position;

                /// @brief contains the size and position of the viewport.
                struct Viewport
                {
                    Progator::Types::Specifics::Renderer::Size width;
                    Progator::Types::Specifics::Renderer::Size height;
                    Progator::Types::Specifics::Renderer::Position x;
                    Progator::Types::Specifics::Renderer::Position y;
                };
            };
        };
    };
};

#endif