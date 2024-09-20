#include "Progator/Window.hpp"

Progator::Window* Progator::WindowNew()
{
    Progator::Window* proto = new Progator::Window;
    return proto;
}

void Progator::WindowDestroy(Progator::Window* window)
{
    window->pointers->window_destroy(window->backend);
    delete window;
}

void Progator::WindowInit(Progator::Window* window, Progator::Pointers* pointers, Progator::Validator* validator)
{
    window->validator = validator;
    window->pointers = pointers;
    
    window->backend = window->pointers->window_new();
    window->pointers->window_init(window->backend, window->validator);
}

void Progator::WindowSetSize(Progator::Window* window, const Progator::U16 width, const Progator::U16 height)
{
    window->pointers->window_set_size(
        window->backend,
        width,
        height
    );
}

void Progator::WindowSetTitle(Progator::Window* window, const Progator::Character *title)
{
    window->pointers->window_set_title(
        window->backend,
        title
    );
}

void Progator::WindowSetVerticalSync(Progator::Window* window, const Progator::U8 enable)
{
    window->pointers->window_set_vertical_sync(
        window->backend,
        enable
    );
}

void Progator::WindowDraw(Progator::Window* window)
{
    window->pointers->window_draw(
        window->backend
    );
}