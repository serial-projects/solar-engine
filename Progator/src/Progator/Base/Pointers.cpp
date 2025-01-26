#include "Progator/Base/Pointers.hpp"
#include "Progator/Backends.hpp"

Progator::Base::Pointers Progator::Base::PointersNew()
{
    Progator::Base::Pointers pointers;
    return pointers;
}

void Progator::Base::PointersDestroy(
    Progator::Base::Pointers* pointers
)
{
    /* NOTE: nothing to be done since everything on the stack! */
    return;
}

void Progator::Base::PointersInit(
    Progator::Base::Pointers* pointers
)
{
    /* Set the mode: */
    pointers->mode = Progator::Base::PointersBackend::NoBackend;
    
    /* Window Pointers: */
    pointers->window_new = nullptr;
    pointers->window_destroy = nullptr;
    pointers->window_init = nullptr;
    pointers->window_set_size = nullptr;
    pointers->window_set_position = nullptr;
    pointers->window_set_title = nullptr;
    pointers->window_set_icon = nullptr;
    pointers->window_get_identity = nullptr;

    /* Renderer Pointers: */
    pointers->renderer_new = nullptr;
    pointers->renderer_destroy = nullptr;
    pointers->renderer_init = nullptr;
    pointers->renderer_attach_another_window = nullptr;
    pointers->renderer_use = nullptr;
    pointers->renderer_set_viewport = nullptr;
    pointers->renderer_adjust_vertical_synchronization = nullptr;
    pointers->renderer_clear = nullptr;
    pointers->renderer_draw = nullptr;

    /* Shaders Pointers: */
    pointers->shader_new = nullptr;
    pointers->shader_destroy = nullptr;
    pointers->shader_init = nullptr;
    pointers->shader_set_vertex_code = nullptr;
    pointers->shader_set_fragment_code = nullptr;
    pointers->shader_set_geometry_code = nullptr;
    pointers->shader_link = nullptr;
    pointers->shader_compile = nullptr;
    pointers->shader_clean = nullptr;
    pointers->shader_use = nullptr;
    pointers->shader_set_uniform_matrix44 = nullptr;
    pointers->shader_set_uniform_matrix33 = nullptr;
    pointers->shader_set_uniform_vector4 = nullptr;
    pointers->shader_set_uniform_vector3 = nullptr;
    pointers->shader_set_uniform_i32 = nullptr;
    pointers->shader_set_uniform_u32 = nullptr;
    pointers->shader_set_uniform_f32 = nullptr;
}

// (A)ssign (V)alue to (O)penGL (Backend)
#define AVO(key, bn)                                                                                \
    pointers->key = (Progator::Base::BackendBinding::bn)(Progator::Backends::OpenGL::bn);

void Progator::Base::PointersSetOpenGLMode(
    Progator::Base::Pointers* pointers
)
{
    /* Set the mode: */
    pointers->mode = Progator::Base::PointersBackend::OpenGL;
    
    /* Set the window: */
    AVO(window_new, WindowNew);
    AVO(window_destroy, WindowDestroy);
    AVO(window_init, WindowInit);
    AVO(window_set_size, WindowSetSize);
    AVO(window_set_position, WindowSetPosition);
    AVO(window_set_title, WindowSetTitle);
    AVO(window_set_icon, WindowSetIcon);
    AVO(window_get_identity, WindowGetIdentity);

    /* Set the renderer: */
    AVO(renderer_new, RendererNew);
    AVO(renderer_destroy, RendererDestroy);
    AVO(renderer_init, RendererInit);
    AVO(renderer_attach_another_window, RendererAttachAnotherWindow);
    AVO(renderer_use, RendererUse);
    AVO(renderer_set_viewport, RendererSetViewport);
    AVO(renderer_adjust_vertical_synchronization, RendererAdjustVerticalSynchronization);
    AVO(renderer_clear, RendererClear);
    AVO(renderer_draw, RendererDraw);

    /* Set the shader: */
    AVO(shader_new, ShaderNew);
    AVO(shader_destroy, ShaderDestroy);
    AVO(shader_init, ShaderInit);
    AVO(shader_set_vertex_code, ShaderSetVertexCode);
    AVO(shader_set_fragment_code, ShaderSetFragmentCode);
    AVO(shader_set_geometry_code, ShaderSetGeometryCode);
    AVO(shader_link, ShaderLink);
    AVO(shader_compile, ShaderCompile);
    AVO(shader_clean, ShaderClean);
    AVO(shader_use, ShaderUse);
    AVO(shader_set_uniform_matrix44, ShaderSetUniformMatrix44);
    AVO(shader_set_uniform_matrix33, ShaderSetUniformMatrix33);
    AVO(shader_set_uniform_vector4, ShaderSetUniformVector4);
    AVO(shader_set_uniform_vector3, ShaderSetUniformVector3);
    AVO(shader_set_uniform_i32, ShaderSetUniformI32);
    AVO(shader_set_uniform_u32, ShaderSetUniformU32);
    AVO(shader_set_uniform_f32, ShaderSetUniformF32);
}