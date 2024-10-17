#include "Progator/Pointers.hpp"

Progator::Pointers* Progator::PointersNew()
{
    Progator::Pointers* proto = new Progator::Pointers;
    return proto;
}

void Progator::PointersDestroy(Progator::Pointers* pointers)
{
    delete pointers;
}

void Progator::PointersUseOpenGLBackend(Progator::Pointers* pointers)
{
    #define register_opengl_function(name,function_type) \
        pointers->name = (Progator::Integrators::function_type)(Progator::Backends::OpenGL::function_type);
    
    /* WINDOW: */
    register_opengl_function(window_new, WindowNew);
    register_opengl_function(window_destroy, WindowDestroy);
    register_opengl_function(window_init, WindowInit);
    register_opengl_function(window_set_size, WindowSetSize);
    register_opengl_function(window_set_title, WindowSetTitle);
    register_opengl_function(window_set_vertical_sync, WindowSetVerticalSync);
    register_opengl_function(window_set_icon, WindowSetIcon);
    register_opengl_function(window_draw, WindowDraw);
    
    /* RENDERER: */
    register_opengl_function(renderer_new, RendererNew);
    register_opengl_function(renderer_destroy, RendererDestroy);
    register_opengl_function(renderer_init, RendererInit);
    register_opengl_function(renderer_set_viewport, RendererSetViewport);
    register_opengl_function(renderer_clear, RendererClear);
    register_opengl_function(renderer_draw, RendererDraw);

    /* MESH: */
    register_opengl_function(mesh_new, MeshNew);
    register_opengl_function(mesh_destroy, MeshDestroy);
    register_opengl_function(mesh_init, MeshInit);
    register_opengl_function(mesh_load_vertexnor, MeshLoadVerTexNor);
    register_opengl_function(mesh_draw, MeshDraw);

    /* SHADER: */
    register_opengl_function(shader_new, ShaderNew);
    register_opengl_function(shader_destroy, ShaderDestroy);
    register_opengl_function(shader_init, ShaderInit);
    register_opengl_function(shader_load_vertex_code_from_file, ShaderLoadVertexCodeFromFile);
    register_opengl_function(shader_load_fragment_code_from_file, ShaderLoadFragmentCodeFromFile);
    register_opengl_function(shader_compile, ShaderCompile);
    register_opengl_function(shader_use, ShaderUse);
    register_opengl_function(shader_su_matrix44, ShaderSUMatrix44);
    register_opengl_function(shader_su_matrix33, ShaderSUMatrix33);
    register_opengl_function(shader_su_matrix22, ShaderSUMatrix22);
    register_opengl_function(shader_su_vector4, ShaderSUVector4);
    register_opengl_function(shader_su_vector3, ShaderSUVector3);
    register_opengl_function(shader_su_vector2, ShaderSUVector2);
    register_opengl_function(shader_su_integer, ShaderSUInteger);
    register_opengl_function(shader_su_uinteger, ShaderSUUInteger);
    register_opengl_function(shader_su_rgba84, ShaderSURGBA84);
    register_opengl_function(shader_su_decimal, ShaderSUDecimal);
    
    /* TEXTURE: */
    register_opengl_function(texture_new, TextureNew);
    register_opengl_function(texture_destroy, TextureDestroy);
    register_opengl_function(texture_init, TextureInit);
    register_opengl_function(texture_load_from_file, TextureLoadFromFile);
    register_opengl_function(texture_use, TextureUse);

    #undef register_opengl_function
}

void Progator::PointersUseVulkanBackend(Progator::Pointers* pointers)
{

}