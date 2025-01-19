#ifndef ProgatorBackendsOpenGLRenderer_hpp
#define ProgatorBackendsOpenGLRenderer_hpp

#include "Progator/Types.hpp"
#include "Progator/Backends/OpenGL/Types.hpp"
#include "Progator/Backends/OpenGL/Window.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            /// @brief The renderer in all the backends are to contain the instance of the GL we are
            /// using, her on OpenGL it is the gl_context. The renderer always take the parameter to
            /// the window (attached_window) in all backends.
            struct Renderer
            {
                SDL_GLContext gl_context;
                Progator::Backends::OpenGL::Window* attached_window;
                Progator::Types::Tuning::Engine::Properties* properties;
                Logica::Control::Validator* validator;
            };
            Progator::Backends::OpenGL::Renderer* RendererNew();
            void RendererDestroy(Progator::Backends::OpenGL::Renderer* renderer);
            void RendererInit(Progator::Backends::OpenGL::Renderer* renderer, Progator::Backends::OpenGL::Window* window, Logica::Control::Validator* validator);
            void RendererAttachAnotherWindow(Progator::Backends::OpenGL::Renderer* renderer, Progator::Backends::OpenGL::Window* window);
            void RendererUse(Progator::Backends::OpenGL::Renderer* renderer);
            void RendererSetViewport(Progator::Backends::OpenGL::Renderer* renderer, Progator::Types::Specifics::Renderer::Viewport& viewport);
            void RendererAdjustVerticalSynchronization(Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::Boolean do_vsync);
            void RendererClear(Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::U32 color);
            void RendererDraw(Progator::Backends::OpenGL::Renderer* renderer);
        };
    };
};

#endif