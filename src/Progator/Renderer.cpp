#include "Progator/Renderer.hpp"

Progator::Renderer* Progator::RendererNew()
{
    Progator::Renderer* proto = new Progator::Renderer;
    return proto;
}

void Progator::RendererDestroy(Progator::Renderer* renderer)
{
    renderer->pointers->renderer_destroy(renderer->backend);
    delete renderer;
}

void Progator::RendererInit(Progator::Renderer* renderer, Progator::Pointers* pointers, Progator::Validator* validator)
{
    renderer->pointers = pointers;
    renderer->validator = validator;

    renderer->backend = renderer->pointers->renderer_new();
    renderer->pointers->renderer_init(renderer->backend, renderer->validator);
}

void Progator::RendererSetViewport(Progator::Renderer* renderer, const Progator::U16 width, const Progator::U16 height, const Progator::U16 x, const Progator::U16 y)
{
    renderer->pointers->renderer_set_viewport(
        renderer->backend,
        width,
        height,
        x,
        y
    );

    /* set the render the viewport property: */
    renderer->width = width,    renderer->height    = height;
    renderer->x     = x,        renderer->y         = y;
}

void Progator::RendererClear(Progator::Renderer* renderer, const Progator::RGBA84 color)
{
    renderer->pointers->renderer_clear(
        renderer->backend,
        color
    );
}

void Progator::RendererDraw(Progator::Renderer* renderer)
{
    renderer->pointers->renderer_draw(
        renderer->backend
    );
}