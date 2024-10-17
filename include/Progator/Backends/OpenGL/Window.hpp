#ifndef ProgatorBackendsOpenGLWindow_hpp
#define ProgatorBackendsOpenGLWindow_hpp

#include "Progator/Backends/OpenGL/Basics.hpp"
#include "Progator/Validator.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            typedef struct Window
            {
                SDL_Window*             os_window;
                SDL_GLContext           gl_context;
                Progator::Validator*    validator;
            } Window;

            Progator::Backends::OpenGL::Window* WindowNew();
            void WindowDestroy(Progator::Backends::OpenGL::Window* window);
            void WindowInit(Progator::Backends::OpenGL::Window* window, Progator::Validator* validator);
            void WindowSetSize(Progator::Backends::OpenGL::Window* window, const Progator::U16 width, const Progator::U16 height);
            void WindowSetTitle(Progator::Backends::OpenGL::Window* window, const Progator::Character* title);
            void WindowSetVerticalSync(Progator::Backends::OpenGL::Window* backend, const Progator::U8 enable);
            void WindowSetIcon(Progator::Backends::OpenGL::Window* backend, const Progator::Character* path);
            void WindowDraw(Progator::Backends::OpenGL::Window* window);
        };
    };
};

#endif