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

            /* Shader: */
            typedef void*(*ShaderNew)();
            typedef void(*ShaderDestroy)(void* shader, void* renderer);
            typedef void(*ShaderInit)(void* shader, void* renderer, Logica::Control::Validator* validator);
            typedef void(*ShaderSetVertexCode)(void* shader, void* renderer, const Progator::Types::Basic::CH8* code);
            typedef void(*ShaderSetFragmentCode)(void* shader, void* renderer, const Progator::Types::Basic::CH8* code);
            typedef void(*ShaderSetGeometryCode)(void* shader, void* renderer, const Progator::Types::Basic::CH8* code);
            typedef void(*ShaderLink)(void* shader, void* renderer);
            typedef void(*ShaderCompile)(void* shader, void* renderer);
            typedef void(*ShaderClean)(void* shader, void* renderer);
            typedef void(*ShaderUse)(void* shader, void* renderer);
            typedef void(*ShaderSetUniformMatrix44)(void* shader, void* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Matrix44 value);
            typedef void(*ShaderSetUniformMatrix33)(void* shader, void* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Matrix33 value);
            typedef void(*ShaderSetUniformVector4)(void* shader, void* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Vector4 value);
            typedef void(*ShaderSetUniformVector3)(void* shader, void* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Vector3 value);
            typedef void(*ShaderSetUniformI32)(void* shader, void* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::I32 value);
            typedef void(*ShaderSetUniformU32)(void* shader, void* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::U32 value);
            typedef void(*ShaderSetUniformF32)(void* shader, void* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::F32 value);
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
            
            /* Shader Pointers: */
            Progator::Base::BackendBinding::ShaderNew shader_new;
            Progator::Base::BackendBinding::ShaderDestroy shader_destroy;
            Progator::Base::BackendBinding::ShaderInit shader_init;
            Progator::Base::BackendBinding::ShaderSetVertexCode shader_set_vertex_code;
            Progator::Base::BackendBinding::ShaderSetFragmentCode shader_set_fragment_code;
            Progator::Base::BackendBinding::ShaderSetGeometryCode shader_set_geometry_code;
            Progator::Base::BackendBinding::ShaderLink shader_link;
            Progator::Base::BackendBinding::ShaderCompile shader_compile;
            Progator::Base::BackendBinding::ShaderClean shader_clean;
            Progator::Base::BackendBinding::ShaderUse shader_use;
            Progator::Base::BackendBinding::ShaderSetUniformMatrix44 shader_set_uniform_matrix44;
            Progator::Base::BackendBinding::ShaderSetUniformMatrix33 shader_set_uniform_matrix33;
            Progator::Base::BackendBinding::ShaderSetUniformVector4 shader_set_uniform_vector4;
            Progator::Base::BackendBinding::ShaderSetUniformVector3 shader_set_uniform_vector3;
            Progator::Base::BackendBinding::ShaderSetUniformI32 shader_set_uniform_i32;
            Progator::Base::BackendBinding::ShaderSetUniformU32 shader_set_uniform_u32;
            Progator::Base::BackendBinding::ShaderSetUniformF32 shader_set_uniform_f32;

            /* mode: */
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