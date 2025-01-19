#ifndef ProgatorBaseWindow_hpp
#define ProgatorBaseWindow_hpp

#include "Progator/Types.hpp"
#include "Progator/Base/Pointers.hpp"

namespace Progator
{
    namespace Base
    {
        struct Window
        {
            /* Backend: */
            void* backend;
            Progator::Base::Pointers* pointers;

            /* Internals: */
            Progator::Types::Specifics::Window::Geometry geometry;
            Progator::Types::Specifics::Window::Id id;
            Logica::Control::Validator* validator;
        };
        Progator::Base::Window WindowNew();
        void WindowDestroy(Progator::Base::Window* window);
        void WindowInit(Progator::Base::Window* window, Progator::Base::Pointers* pointers, Logica::Control::Validator* validator);
        void windowSetSize(Progator::Base::Window* window, const Progator::Types::Specifics::Window::Size width, const Progator::Types::Specifics::Window::Size height);
        void WindowSetPosition(Progator::Base::Window* window, const Progator::Types::Specifics::Window::Position x, const Progator::Types::Specifics::Window::Size y);
        void WindowSetTitle(Progator::Base::Window* window, const Progator::Types::Basic::CH8* title);
        void WindowSetIcon(Progator::Base::Window* window, const SDL_Surface* surface);
        Progator::Types::Specifics::Window::Id WindowGetIdentity(Progator::Base::Window* window);
    };
};

#endif