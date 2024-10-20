#include "Progator/Backends/OpenGL/Window.hpp"
#include "Progator/Values.hpp"

#include <SDL2/SDL_image.h>

Progator::Backends::OpenGL::Window* Progator::Backends::OpenGL::WindowNew()
{
    Progator::Backends::OpenGL::Window* proto = new Progator::Backends::OpenGL::Window;
    return proto;
}

void Progator::Backends::OpenGL::WindowDestroy(Progator::Backends::OpenGL::Window* window)
{
    SDL_GL_DeleteContext(window->gl_context);
    SDL_DestroyWindow(window->os_window);
    delete window;
}

void Progator::Backends::OpenGL::WindowInit(Progator::Backends::OpenGL::Window* window, Progator::Validator* validator)
{
    window->validator = validator;

    /* set GL options: */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    /* Begin SDL's Window: */
    window->os_window = SDL_CreateWindow(
        "[Progator Initial Window]",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        640,
        SDL_WINDOW_OPENGL
    );

    /* begin SDL's GL context: */
    window->gl_context = SDL_GL_CreateContext(window->os_window);

    /* Initialize GLEW: */
    glewExperimental = GL_TRUE;
    glewInit();

    /* NOTE: attach the message debug system: */
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(Progator::Backends::OpenGL::MessageCallback, 0);
}

void Progator::Backends::OpenGL::WindowSetSize(Progator::Backends::OpenGL::Window* window, const Progator::U16 width, const Progator::U16 height)
{
    SDL_SetWindowSize(
        window->os_window,
        (int)width,
        (int)height
    );
    SDL_SetWindowPosition(
        window->os_window,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED
    );
}

void Progator::Backends::OpenGL::WindowSetTitle(Progator::Backends::OpenGL::Window* window, const Progator::Character* title)
{
    SDL_SetWindowTitle(
        window->os_window,
        ((const char*)title)
    );
}

void Progator::Backends::OpenGL::WindowSetVerticalSync(Progator::Backends::OpenGL::Window* backend, const Progator::U8 enable)
{
    switch(enable)
    {
        case PROGATOR_YES:
            if(SDL_GL_SetSwapInterval(-1) < 0)
                SDL_GL_SetSwapInterval(1);
            break;
        default:
            SDL_GL_SetSwapInterval(0);
            break;
    };
}

void Progator::Backends::OpenGL::WindowSetIcon(Progator::Backends::OpenGL::Window* backend, const Progator::Character* path)
{
    SDL_Surface* image_surface = IMG_Load(path);
    if(image_surface != NULL)
    {
        SDL_SetWindowIcon(backend->os_window, image_surface);
        SDL_FreeSurface(image_surface);
    }
    else
    {
        Progator::ValidatorError(
            backend->validator,
            Progator::ValidatorCodes::NoFile,
            "No file %s found to set window icon",
            path
        );
    }
}

void Progator::Backends::OpenGL::WindowDraw(Progator::Backends::OpenGL::Window* window)
{
    SDL_GL_SwapWindow(window->os_window);
}