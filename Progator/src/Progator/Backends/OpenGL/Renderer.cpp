#include "Progator/Backends/OpenGL/Renderer.hpp"
#include "Progator/Config.hpp"
#include "Progator/Validator.hpp"

#ifdef PROGATOR_DEBUG
    #include <iostream>
#endif

Progator::Backends::OpenGL::Renderer* Progator::Backends::OpenGL::RendererNew()
{
    Progator::Backends::OpenGL::Renderer* renderer = new Progator::Backends::OpenGL::Renderer;
    return renderer;
}

void Progator::Backends::OpenGL::RendererDestroy(
    Progator::Backends::OpenGL::Renderer* renderer
)
{
    SDL_GL_DeleteContext(renderer->gl_context);
    delete renderer;
}

void Progator::Backends::OpenGL::RendererInit(
    Progator::Backends::OpenGL::Renderer* renderer,
    Progator::Backends::OpenGL::Window* window,
    Logica::Control::Validator* validator
)
{
    renderer->attached_window = window;
    renderer->validator = validator;
    
    /* Set the hints for the OpenGL context creation: */
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION,
        PROGATOR_BACKENDS_OPENGL_RENDERER_MAJOR_VERSION
    );
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION,
        PROGATOR_BACKENDS_OPENGL_RENDERER_MINOR_VERSION
    );
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );
    SDL_GL_SetAttribute(
        SDL_GL_STENCIL_SIZE,
        8
    );
    
    /* Assign some variables because we will enter label space! */
    GLenum glew_result;

    /* initialize an instance: */
    renderer->gl_context = SDL_GL_CreateContext(renderer->attached_window->os_window);
    if(renderer->gl_context == nullptr)
    {
        renderer->validator->SetError(
            Progator::ValidatorCodes::FailedInitializeOpenGLBackendDueBadOpenGLContext,
            "Failed to initialize OpenGL Backend due error while creating context: %s",
            SDL_GetError()
        );
        goto error;
    }
    else
        SDL_GL_MakeCurrent(renderer->attached_window->os_window, renderer->gl_context);

    /* initialize GLEW: */
    glewExperimental    = GL_TRUE;
    glew_result         = glewInit();
    if(glew_result != GLEW_OK)
    {
        renderer->validator->SetError(
            Progator::ValidatorCodes::FailedInitializeOpenGLBackendDueBadGLEWInit,
            "Failed to initialize OpenGL Backend due GLEW error: %s",
            glewGetErrorString(glew_result)
        );
        goto error;
    }

    /* Set some OpenGL features enabled by default: */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);

    /* NOTE: some debug information for you: */
    #ifdef PROGATOR_DEBUG
        std::cout
            << __PRETTY_FUNCTION__
            << ": GL Vendor = "
            << glGetString(GL_VENDOR)
            << "\n"
            << __PRETTY_FUNCTION__
            << ": GL Renderer = "
            << glGetString(GL_RENDERER)
            << "\n"
            << __PRETTY_FUNCTION__
            << ": GL Version = "
            << glGetString(GL_VERSION)
            << "\n";
    #endif

    error:
    return;
}

void Progator::Backends::OpenGL::RendererAttachAnotherWindow(
    Progator::Backends::OpenGL::Renderer* renderer,
    Progator::Backends::OpenGL::Window* window
)
{
    renderer->attached_window = window;
    SDL_GL_MakeCurrent(
        renderer->attached_window->os_window,
        renderer->gl_context
    );
}

void Progator::Backends::OpenGL::RendererUse(
    Progator::Backends::OpenGL::Renderer* renderer
)
{
    SDL_GL_MakeCurrent(
        renderer->attached_window->os_window,
        renderer->gl_context
    );
}

void Progator::Backends::OpenGL::RendererSetViewport(
    Progator::Backends::OpenGL::Renderer* renderer,
    Progator::Types::Specifics::Renderer::Viewport& viewport
)
{
    glViewport(
        (GLint)(viewport.x),
        (GLint)(viewport.y),
        (GLsizei)(viewport.width),
        (GLsizei)(viewport.height)
    );
}

void Progator::Backends::OpenGL::RendererAdjustVerticalSynchronization(
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Basic::Boolean do_vsync
)
{
    if(do_vsync)
    {
        /* enter vsync attempting: */
        if(SDL_GL_SetSwapInterval(-1) < 0)
            SDL_GL_SetSwapInterval(1);
    }
    else
        SDL_GL_SetSwapInterval(0);
}

void Progator::Backends::OpenGL::RendererClear(
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Basic::U32 color
)
{
    const Progator::Types::Basic::U8 R = ((color & 0xFF000000) >> 24);
    const Progator::Types::Basic::U8 G = ((color & 0x00FF0000) >> 16);
    const Progator::Types::Basic::U8 B = ((color & 0x0000FF00) >>  8);
    const Progator::Types::Basic::U8 A = ((color & 0x000000FF));

    /* do cleaning: */
    glClearColor(
        ((float)R / (float)255),
        ((float)G / (float)255),
        ((float)B / (float)255),
        ((float)A / (float)255)
    );

    glClear(
        GL_COLOR_BUFFER_BIT     | 
        GL_DEPTH_BUFFER_BIT     |
        GL_STENCIL_BUFFER_BIT
    );
}

void Progator::Backends::OpenGL::RendererDraw(
    Progator::Backends::OpenGL::Renderer* renderer
)
{
    /* Update the window: */
    SDL_GL_SwapWindow(renderer->attached_window->os_window);
}