#ifndef ProgatorPointers_hpp
#define ProgatorPointers_hpp

#include "Progator/Types.hpp"
#include "Progator/Validator.hpp"

/* NOTE: this is the only place the backends are actually imported:
 * TODO: use MACROS to check what APIs are available to use;
 */

#include "Progator/Backends/OpenGL/Backend.hpp"

namespace Progator
{
    /* This namespace contains all the function types that connects with the backend side. */
    namespace Integrators
    {
        /* Window: */
        typedef void*(*WindowNew)();
        typedef void(*WindowDestroy)(void *backend);
        typedef void(*WindowInit)(void *backend, Progator::Validator *validator);
        typedef void(*WindowSetSize)(void *backend, const Progator::U16 width, const Progator::U16 height);
        typedef void(*WindowSetTitle)(void *backend, const Progator::Character *title);
        typedef void(*WindowSetVerticalSync)(void *backend, const Progator::U8 enable);
        typedef void(*WindowDraw)(void *backend);

        /* Renderer: */
        typedef void*(*RendererNew)();
        typedef void(*RendererDestroy)(void *backend);
        typedef void(*RendererInit)(void *backend, Progator::Validator *validator);
        typedef void(*RendererSetViewport)(void *backend, const Progator::U16 width, const Progator::U16 height, const Progator::U16 x, const Progator::U16 y);
        typedef void(*RendererClear)(void *backend, const Progator::RGBA84 color);
        typedef void(*RendererDraw)(void *backend);
        
        /* Mesh: */
        typedef void*(*MeshNew)();
        typedef void(*MeshDestroy)(void *backend);
        typedef void(*MeshInit)(void *backend, Progator::Validator *validator);
        typedef void(*MeshLoadVerTexNor)(void *backend, const Progator::F32 data[], const Progator::U32 amount);
        typedef void(*MeshDraw)(void *backend);

        /* Shader: */
        typedef void*(*ShaderNew)();
        typedef void(*ShaderDestroy)(void *backend);
        typedef void(*ShaderInit)(void *backend, Progator::Validator *validator);
        typedef void(*ShaderLoadVertexCodeFromFile)(void *backend, const Progator::Character *path);
        typedef void(*ShaderLoadFragmentCodeFromFile)(void *backend, const Progator::Character *path);
        typedef void(*ShaderCompile)(void *backend);
        typedef void(*ShaderUse)(void *backend);
        typedef void(*ShaderSUMatrix44)(void *backend, const Progator::Character *key, const Progator::Matrix44 value);
        typedef void(*ShaderSUMatrix33)(void *backend, const Progator::Character *key, const Progator::Matrix33 value);
        typedef void(*ShaderSUMatrix22)(void *backend, const Progator::Character *key, const Progator::Matrix22 value);
        typedef void(*ShaderSUVector4)(void *backend, const Progator::Character *key, const Progator::Vector4 value);
        typedef void(*ShaderSUVector3)(void *backend, const Progator::Character *key, const Progator::Vector3 value);
        typedef void(*ShaderSUVector2)(void *backend, const Progator::Character *key, const Progator::Vector2 value);
        typedef void(*ShaderSUInteger)(void *backend, const Progator::Character *key, const Progator::I32 value);
        typedef void(*ShaderSUUInteger)(void *backend, const Progator::Character *key, const Progator::U32 value);
        typedef void(*ShaderSURGBA84)(void *backend, const Progator::Character *key, const Progator::RGBA84 value);
        typedef void(*ShaderSUDecimal)(void *backend, const Progator::Character *key, const Progator::F32 value);

        /* Texture: */
        typedef void*(*TextureNew)();
        typedef void(*TextureDestroy)(void *backend);
        typedef void(*TextureInit)(void *backend, Progator::Validator *validator);
        typedef void(*TextureLoadFromFile)(void *backend, const Progator::Character *path);
        typedef void(*TextureUse)(void *backend);
    };
    
    typedef struct Pointers
    {
        /* Progator/Window: */
        Progator::Integrators::WindowNew                window_new;
        Progator::Integrators::WindowDestroy            window_destroy;
        Progator::Integrators::WindowInit               window_init;
        Progator::Integrators::WindowSetSize            window_set_size;
        Progator::Integrators::WindowSetTitle           window_set_title;
        Progator::Integrators::WindowSetVerticalSync    window_set_vertical_sync;
        Progator::Integrators::WindowDraw               window_draw;

        /* Progator/Renderer: */
        Progator::Integrators::RendererNew          renderer_new;
        Progator::Integrators::RendererDestroy      renderer_destroy;
        Progator::Integrators::RendererInit         renderer_init;
        Progator::Integrators::RendererSetViewport  renderer_set_viewport;
        Progator::Integrators::RendererClear        renderer_clear;
        Progator::Integrators::RendererDraw         renderer_draw;
        
        /* Progator/Mesh: */
        Progator::Integrators::MeshNew              mesh_new;
        Progator::Integrators::MeshDestroy          mesh_destroy;
        Progator::Integrators::MeshInit             mesh_init;
        Progator::Integrators::MeshLoadVerTexNor    mesh_load_vertexnor;
        Progator::Integrators::MeshDraw             mesh_draw;

        /* Progator/Shader: */
        Progator::Integrators::ShaderNew                        shader_new;
        Progator::Integrators::ShaderDestroy                    shader_destroy;
        Progator::Integrators::ShaderInit                       shader_init;
        Progator::Integrators::ShaderLoadVertexCodeFromFile     shader_load_vertex_code_from_file;
        Progator::Integrators::ShaderLoadFragmentCodeFromFile   shader_load_fragment_code_from_file;
        Progator::Integrators::ShaderCompile                    shader_compile;
        Progator::Integrators::ShaderUse                        shader_use;
        Progator::Integrators::ShaderSUMatrix44                 shader_su_matrix44;
        Progator::Integrators::ShaderSUMatrix33                 shader_su_matrix33;
        Progator::Integrators::ShaderSUMatrix22                 shader_su_matrix22;
        Progator::Integrators::ShaderSUVector4                  shader_su_vector4;
        Progator::Integrators::ShaderSUVector3                  shader_su_vector3;
        Progator::Integrators::ShaderSUVector2                  shader_su_vector2;
        Progator::Integrators::ShaderSUInteger                  shader_su_integer;
        Progator::Integrators::ShaderSUUInteger                 shader_su_uinteger;
        Progator::Integrators::ShaderSURGBA84                   shader_su_rgba84;
        Progator::Integrators::ShaderSUDecimal                  shader_su_decimal;

        /* Progator/Texture: */
        Progator::Integrators::TextureNew           texture_new;
        Progator::Integrators::TextureDestroy       texture_destroy;
        Progator::Integrators::TextureInit          texture_init;
        Progator::Integrators::TextureLoadFromFile  texture_load_from_file;
        Progator::Integrators::TextureUse           texture_use;
    } Pointers;

    Progator::Pointers* PointersNew();
    void PointersDestroy(Progator::Pointers* pointers);
    void PointersUseOpenGLBackend(Progator::Pointers* pointers);
    void PointersUseVulkanBackend(Progator::Pointers* pointers);
};

#endif