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
    #define register_function(name,function_type,function) \
        pointers->name = (Progator::Integrators::function_type)(function);
    
    /* WINDOW: */
    register_function(window_new, WindowNew, Progator::Backends::OpenGL::WindowNew);
    register_function(window_destroy, WindowDestroy, Progator::Backends::OpenGL::WindowDestroy);
    register_function(window_init, WindowInit, Progator::Backends::OpenGL::WindowInit);
    register_function(window_set_size, WindowSetSize, Progator::Backends::OpenGL::WindowSetSize);
    register_function(window_set_title, WindowSetTitle, Progator::Backends::OpenGL::WindowSetTitle);
    register_function(window_set_vertical_sync, WindowSetVerticalSync, Progator::Backends::OpenGL::WindowSetVerticalSync);
    register_function(window_draw, WindowDraw, Progator::Backends::OpenGL::WindowDraw);
    
    /* RENDERER: */
    register_function(renderer_new, RendererNew, Progator::Backends::OpenGL::RendererNew);
    register_function(renderer_destroy, RendererDestroy, Progator::Backends::OpenGL::RendererDestroy);
    register_function(renderer_init, RendererInit, Progator::Backends::OpenGL::RendererInit);
    register_function(renderer_set_viewport, RendererSetViewport, Progator::Backends::OpenGL::RendererSetViewport);
    register_function(renderer_clear, RendererClear, Progator::Backends::OpenGL::RendererClear);
    register_function(renderer_draw, RendererDraw, Progator::Backends::OpenGL::RendererDraw);

    #undef register_function
}

void Progator::PointersUseVulkanBackend(Progator::Pointers* pointers)
{

}