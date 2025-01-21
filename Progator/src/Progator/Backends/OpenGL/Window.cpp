#include "Progator/Backends/OpenGL/Window.hpp"
#include "Progator/Validator.hpp"
#include "Progator/Config.hpp"

Progator::Backends::OpenGL::Window* Progator::Backends::OpenGL::WindowNew()
{
    Progator::Backends::OpenGL::Window* window = new Progator::Backends::OpenGL::Window;
    return window;
}

void Progator::Backends::OpenGL::WindowDestroy(
    Progator::Backends::OpenGL::Window* window
)
{
    SDL_DestroyWindow(window->os_window);
    delete window;
}

void Progator::Backends::OpenGL::WindowInit(
    Progator::Backends::OpenGL::Window* window,
    Logica::Control::Validator* validator
)
{
    window->validator = validator;
    window->os_window = SDL_CreateWindow(
        "[" PROGATOR_VERSION_FULLNAME " (OpenGL 3.3 Backend)]",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        640,
        SDL_WINDOW_OPENGL
    );
    if(window->os_window == nullptr)
        window->validator->SetError(
            Progator::ValidatorCodes::FailedInitializeOpenGLBackendDueSDLWindowCreateError,
            "Failed to initialize OpenGL Backend due SDL_CreateWindow error: %s",
            SDL_GetError()
        );
}

void Progator::Backends::OpenGL::WindowSetSize(
    Progator::Backends::OpenGL::Window* window,
    const Progator::Types::Specifics::Window::Size width,
    const Progator::Types::Specifics::Window::Size height
)
{
    SDL_SetWindowSize(
        window->os_window,
        width,
        height
    );
}

void Progator::Backends::OpenGL::WindowSetPosition(
    Progator::Backends::OpenGL::Window* window,
    const Progator::Types::Specifics::Window::Position x,
    const Progator::Types::Specifics::Window::Position y
)
{
    SDL_SetWindowPosition(
        window->os_window,
        x,
        y
    );
}

void Progator::Backends::OpenGL::WindowSetTitle(
    Progator::Backends::OpenGL::Window* window,
    const Progator::Types::Basic::CH8* title
)
{
    SDL_SetWindowTitle(
        window->os_window,
        title
    );
}

void Progator::Backends::OpenGL::WindowSetIcon(
    Progator::Backends::OpenGL::Window* window,
    SDL_Surface* surface
)
{
    SDL_SetWindowIcon(
        window->os_window,
        surface
    );
}

Progator::Types::Specifics::Window::Id Progator::Backends::OpenGL::WindowGetIdentity(
    Progator::Backends::OpenGL::Window* window
)
{
    Uint32 window_id = SDL_GetWindowID(window->os_window);
    return (Progator::Types::Specifics::Window::Id)(window_id);
}