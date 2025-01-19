#ifndef ProgatorTypesSpecificsWindow_hpp
#define ProgatorTypesSpecificsWindow_hpp

#include "Progator/Types/Basic.hpp"

namespace Progator
{
    namespace Types
    {
        namespace Specifics
        {
            namespace Window
            {
                /// @brief type for the window size.s
                typedef Progator::Types::Basic::U16 Size;

                /// @brief type for the windoww position.
                typedef Progator::Types::Basic::U16 Position;

                /// @brief used by SDL to return the window size.
                typedef Progator::Types::Basic::U32 Id;

                /// @brief contains the window dimensions!
                struct Geometry
                {
                    Progator::Types::Specifics::Window::Size width;
                    Progator::Types::Specifics::Window::Size height;
                    Progator::Types::Specifics::Window::Position x;
                    Progator::Types::Specifics::Window::Position y;
                };
            };
        };
    };
};

#endif