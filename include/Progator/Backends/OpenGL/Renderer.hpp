#ifndef ProgatorBackendsOpenGLRenderer_hpp
#define ProgatorBackendsOpenGLRenderer_hpp

#include "Progator/Backends/OpenGL/Basics.hpp"
#include "Progator/Validator.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            /* NOTE:
             * OpenGL don't require an complex renderer initialization and instantiation unlike
             * for example, Vulkan, that require an complex setup to work.
             */

            typedef struct Renderer
            {
                Progator::Validator*        validator;
            } Renderer;

            Progator::Backends::OpenGL::Renderer* RendererNew();
            void RendererDestroy(Progator::Backends::OpenGL::Renderer* renderer);
            void RendererInit(Progator::Backends::OpenGL::Renderer* renderer, Progator::Validator* validator);
            void RendererSetViewport(Progator::Backends::OpenGL::Renderer* backend, const Progator::U16 width, const Progator::U16 height, const Progator::U16 x, const Progator::U16 y);
            void RendererClear(Progator::Backends::OpenGL::Renderer* backend, const Progator::RGBA84 color);
            void RendererDraw(Progator::Backends::OpenGL::Renderer* backend);
        };
    };
};

#endif