#ifndef ProgatorBasePointers_hpp
#define ProgatorBasePointers_hpp

#include "Progator/Types.hpp"

namespace Progator
{
    namespace Base
    {
        namespace PointersBackend
        {
            enum PointersBackend
            {
                NoBackend = 0,
                OpenGL, 
                Vulkan,
                DirectX,
                Metal,
                GLES,
                Unknown = UINT8_MAX
            };
        };

        /// @brief contains the bindings.
        namespace BackendBinding
        {            
            /* Window: */
            typedef void*(*WindowNew)();
            typedef void(*WindowDestroy)(void* window);
            typedef void(*WindowInit)(void* window, Logica::Control::Validator* validator);
            typedef void(*WindowSetSize)(void* window, const Progator::Types::Specifics::Window::Size width, const Progator::Types::Specifics::Window::Size height);
            typedef void(*WindowSetPosition)(void* window, const Progator::Types::Specifics::Window::Position x, const Progator::Types::Specifics::Window::Size y);
            typedef void(*WindowSetTitle)(void* window, const Progator::Types::Basic::CH8* title);
            typedef void(*WindowSetIcon)(void* window, SDL_Surface* surface);
            typedef Progator::Types::Specifics::Window::Id(*WindowGetIdentity)(void* window);

            /* Renderer: */    
            typedef void*(*RendererNew)();
            typedef void(*RendererDestroy)(void* renderer);
            typedef void(*RendererInit)(void* renderer, void* window, Logica::Control::Validator* validator);
            typedef void(*RendererAttachAnotherWindow)(void* renderer, void* window);
            typedef void(*RendererUse)(void* renderer);
            typedef void(*RendererSetViewport)(void* renderer, const Progator::Types::Specifics::Renderer::Viewport& viewport);
            typedef void(*RendererAdjustVerticalSynchronization)(void* renderer, const Progator::Types::Basic::Boolean do_vsync);
            typedef void(*RendererClear)(void* renderer, const Progator::Types::Basic::U32 color);
            typedef void(*RendererDraw)(void* renderer);    
        };

        /// @brief contains the pointers for the backend functions.
        struct Pointers
        {
            /* Window Pointers: */
            Progator::Base::BackendBinding::WindowNew window_new;
            Progator::Base::BackendBinding::WindowDestroy window_destroy;
            Progator::Base::BackendBinding::WindowInit window_init;
            Progator::Base::BackendBinding::WindowSetSize window_set_size;
            Progator::Base::BackendBinding::WindowSetPosition window_set_position;
            Progator::Base::BackendBinding::WindowSetTitle window_set_title;
            Progator::Base::BackendBinding::WindowSetIcon window_set_icon;
            Progator::Base::BackendBinding::WindowGetIdentity window_get_identity;

            /* Renderer Pointers: */
            Progator::Base::BackendBinding::RendererNew renderer_new;
            Progator::Base::BackendBinding::RendererDestroy renderer_destroy;
            Progator::Base::BackendBinding::RendererInit renderer_init;
            Progator::Base::BackendBinding::RendererAttachAnotherWindow renderer_attach_another_window;
            Progator::Base::BackendBinding::RendererUse renderer_use;
            Progator::Base::BackendBinding::RendererSetViewport renderer_set_viewport;
            Progator::Base::BackendBinding::RendererAdjustVerticalSynchronization renderer_adjust_vertical_synchronization;
            Progator::Base::BackendBinding::RendererClear renderer_clear;
            Progator::Base::BackendBinding::RendererDraw renderer_draw;

            Progator::Types::Basic::U8 mode;
        };
        /// @brief Creates a new Pointers for your selected backend (use Set<Backend>Mode function)!
        /// @return return the empty Pointers structure.
        Progator::Base::Pointers PointersNew();

        /// @brief Destroys the Pointers that you made.
        /// @param pointers the pointers to be destroyed.
        void PointersDestroy(Progator::Base::Pointers* pointers);

        /// @brief Init the pointers (this won't select an API, it is just to avoid uninitialized
        /// memory spaces on valgrind?)
        /// @param pointers the pointers to initialize.
        void PointersInit(Progator::Base::Pointers* pointers);

        /// @brief Attach the pointers to use the OpenGL backend (YOU should only call this during
        /// the initialization and NEVER during the program since the pointers WON'T be freeing the
        /// memories automatically).
        /// @param pointers the pointers set the OpenGL.
        void PointersSetOpenGLMode(Progator::Base::Pointers* pointers);
    };
};

#endif