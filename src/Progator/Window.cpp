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
    window->validator   = validator;
    window->pointers    = pointers;
    
    window->backend = window->pointers->window_new();
    if(window->backend == nullptr)
    {
        Progator::ValidatorError(
            window->validator,
            Progator::ValidatorCodes::FailedToCreateObject,
            "Failed to create window object."
        );
    }
    else
    {
        window->pointers->window_init(window->backend, window->validator);
    }
}

void Progator::WindowSetSize(Progator::Window* window, const Progator::U16 width, const Progator::U16 height)
{
    ProgatorHelperPerformWhenValidated(
        window->validator,
        {
            window->pointers->window_set_size(
                window->backend,
                width,
                height
            );
            window->width = width;
            window->height = height;
        }
    );
}

void Progator::WindowSetTitle(Progator::Window* window, const Progator::Character *title)
{
    ProgatorHelperPerformWhenValidated(
        window->validator,
        {
            window->pointers->window_set_title(
                window->backend,
                title
            );
        }
    );
}

void Progator::WindowSetVerticalSync(Progator::Window* window, const Progator::U8 enable)
{
    ProgatorHelperPerformWhenValidated(
        window->validator,
        {
            window->pointers->window_set_vertical_sync(
                window->backend,
                enable
            );
        }
    );
}

void Progator::WindowDraw(Progator::Window* window)
{
    ProgatorHelperPerformWhenValidated(
        window->validator,
        {
            window->pointers->window_draw(
                window->backend
            );
        }
    );
}

#include <SDL2/SDL_image.h>

void Progator::WindowSetIcon(Progator::Window* window, const Progator::Character* path)
{
    ProgatorHelperPerformWhenValidated(
        window->validator,
        {
            /* NOTE: since everything is SDL, we don't need any backend function to set the icon
             * of an window, we just need to tell SDL to load the image for us.
             */
            window->pointers->window_set_icon(
                window->backend,
                path
            );
        }
    );
}