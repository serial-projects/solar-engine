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
                /**
                 * \brief Defines the type to hold the viewport size.
                 */
                typedef Progator::Types::Basic::U16     ViewportSizeType;

                /**
                 * \brief Defines the type to hold the viewport position.
                 */
                typedef Progator::Types::Basic::U16     ViewportPositionType;
                
                /**
                 * \brief Contains all the Viewport information:
                 */
                struct Viewport
                {
                    Progator::Types::Specifics::Renderer::ViewportSizeType      width;
                    Progator::Types::Specifics::Renderer::ViewportSizeType      height;
                    Progator::Types::Specifics::Renderer::ViewportPositionType  X;
                    Progator::Types::Specifics::Renderer::ViewportPositionType  Y;
                };
            };
        };
    };
};

#endif