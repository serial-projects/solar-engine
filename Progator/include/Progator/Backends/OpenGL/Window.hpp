#ifndef ProgatorBackendsOpenGLWindow_hpp
#define ProgatorBackendsOpenGLWindow_hpp

#include "Progator/Types.hpp"
#include "Progator/Backends/OpenGL/Types.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            struct Window
            {
                SDL_Window* os_window;
                Logica::Control::Validator* validator;
            };
            Progator::Backends::OpenGL::Window* WindowNew();
            void WindowDestroy(Progator::Backends::OpenGL::Window* window);
            void WindowInit(Progator::Backends::OpenGL::Window* window, Logica::Control::Validator* validator);
            void WindowSetSize(Progator::Backends::OpenGL::Window* window, const Progator::Types::Specifics::Window::Size width, const Progator::Types::Specifics::Window::Size height);
            void WindowSetPosition(Progator::Backends::OpenGL::Window* window, const Progator::Types::Specifics::Window::Position x, const Progator::Types::Specifics::Window::Position y);
            void WindowSetTitle(Progator::Backends::OpenGL::Window* window, const Progator::Types::Basic::CH8* title);
            void WindowSetIcon(Progator::Backends::OpenGL::Window* window, SDL_Surface* surface);
            Progator::Types::Specifics::Window::Id WindowGetIdentity(Progator::Backends::OpenGL::Window* window);
        };
    };
};


#endif