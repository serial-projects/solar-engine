#ifndef ProgatorTypesSpecificsWindow_hpp
#define ProgatorTypesSpecificsWindow_hpp

#include "Progator/Types/Basic.hpp"

namespace Progator
{
    namespace Types
    {
        namespace Specifics
        {
            /**
             * \brief Contains everything specific to the window element on Progator.
             */
            namespace Window
            {
                /**
                 * \brief Define the type to hold the size of the integer to carry the
                 * window size, on default (or historically) an U16 is enough to store
                 * most than any size window ever have;
                 */
                typedef Progator::Types::Basic::U16 SizeType;

                /**
                 * \brief Define the type to hold the position of an integer to carry the
                 * window position.
                 */
                typedef Progator::Types::Basic::U16 PositionType;

                /**
                 * \brief Contains all the geometry information that the window needs.
                 */
                struct Geometry
                {
                    Progator::Types::Specifics::Window::SizeType        width;
                    Progator::Types::Specifics::Window::SizeType        height;
                    Progator::Types::Specifics::Window::PositionType    X;
                    Progator::Types::Specifics::Window::PositionType    Y;
                };
            }
        };
    };
};

#endif