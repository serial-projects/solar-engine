#include "Progator/Base/Window.hpp"

Progator::Base::Window Progator::Base::WindowNew()
{
    Progator::Base::Window window;
    return window;
}

void Progator::Base::WindowDestroy(Progator::Base::Window* window)
{
    /* Delete the window: */
    window->pointers->window_destroy(window->backend);
}

void Progator::Base::WindowInit(
    Progator::Base::Window* window,
    Progator::Base::Pointers* pointers,
    Logica::Control::Validator* validator
)
{
    window->validator = validator;
    window->pointers = pointers;
    
    /* initialize the backend: */
    
    /* TODO: for all backends, there is a default window size of 800x640, use macro to define this
     * on Progator/Config.hpp area.
     */

    window->backend = window->pointers->window_new();
    window->pointers->window_init(window->pointers, window->validator);
    
    /* TODO: on the future, make some cool bitwise operation to set the window on the center.
     */
    window->geometry = {
        .width  = 800,
        .height = 640,
        .x      = 0,
        .y      = 0
    };

    window->id = window->pointers->window_get_identity(window->backend);
}

void Progator::Base::windowSetSize(
    Progator::Base::Window* window,
    const Progator::Types::Specifics::Window::Size width,
    const Progator::Types::Specifics::Window::Size height
)
{
    window->pointers->window_set_size(
        window->backend,
        width,
        height
    );
    window->geometry.width = width;
    window->geometry.height= height;
}

void Progator::Base::WindowSetPosition(
    Progator::Base::Window* window,
    const Progator::Types::Specifics::Window::Position x,
    const Progator::Types::Specifics::Window::Position y
)
{
    window->pointers->window_set_position(
        window->backend,
        x,
        y
    );
    window->geometry.x = x;
    window->geometry.y = y;
}

void Progator::Base::WindowSetTitle(
    Progator::Base::Window* window,
    const Progator::Types::Basic::CH8* title
)
{
    window->pointers->window_set_title(
        window->backend,
        title
    );
}

void Progator::Base::WindowSetIcon(
    Progator::Base::Window* window,
    SDL_Surface* surface
)
{
    window->pointers->window_set_icon(
        window->backend,
        surface
    );
}

Progator::Types::Specifics::Window::Id Progator::Base::WindowGetIdentity(
    Progator::Base::Window* window
)
{
    /* NOTE: in case the window changes ID? is that even possible? */
    return window->id;
}