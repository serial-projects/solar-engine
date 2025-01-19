#ifndef ProgatorBaseRenderer_hpp
#define ProgatorBaseRenderer_hpp

#include "Progator/Base/Pointers.hpp"
#include "Progator/Base/Window.hpp"
#include "Progator/Types.hpp"

namespace Progator
{
    namespace Base
    {
        struct Renderer
        {
            /* Backend: */
            void* backend;
            Progator::Base::Pointers* pointers;
            
            /* Internals: */
            Progator::Types::Specifics::Renderer::Viewport viewport;
            Logica::Control::Validator* validator;
        };
        Progator::Base::Renderer RendererNew();
        void RendererDestroy(Progator::Base::Renderer* renderer);
        void RendererInit(Progator::Base::Renderer* renderer, Progator::Base::Window* window, Progator::Base::Pointers* pointers, Logica::Control::Validator* validator);
        void RendererAttachAnotherWindow(Progator::Base::Renderer* renderer, Progator::Base::Window* window);
        void RendererUse(Progator::Base::Renderer* renderer);
        void RendererSetViewport(Progator::Base::Renderer* renderer, const Progator::Types::Specifics::Renderer::Viewport& viewport);
        void RendererAdjustVerticalSynchronization(Progator::Base::Renderer* renderer, const Progator::Types::Basic::Boolean do_vsync);
        void RendererClear(Progator::Base::Renderer* renderer, const Progator::Types::Basic::U32 color);
        void RendererDraw(Progator::Base::Renderer* renderer);
    };
};

#endif