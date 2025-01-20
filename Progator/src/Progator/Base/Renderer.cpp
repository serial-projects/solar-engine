#include "Progator/Base/Renderer.hpp"

Progator::Base::Renderer* Progator::Base::RendererNew()
{
    Progator::Base::Renderer* renderer = new Progator::Base::Renderer;
    return renderer;
}

void Progator::Base::RendererDestroy(
    Progator::Base::Renderer* renderer
)
{
    renderer->pointers->renderer_destroy(renderer->backend);
    delete renderer;
}

void Progator::Base::RendererInit(
    Progator::Base::Renderer* renderer,
    Progator::Base::Window* window,
    Progator::Base::Pointers* pointers,
    Logica::Control::Validator* validator
)
{
    renderer->pointers = pointers;
    renderer->validator = validator;
    
    /* Initialize the Renderer: */
    renderer->backend = renderer->pointers->renderer_new();
    renderer->pointers->renderer_init(
        renderer->backend,
        window->backend,
        renderer->validator
    );

    /* set the other properties: */
    renderer->viewport = 
    {
        .width  = 0,
        .height = 0,
        .x = 0,
        .y = 0
    };
}

void Progator::Base::RendererAttachAnotherWindow(
    Progator::Base::Renderer* renderer,
    Progator::Base::Window* window
)
{
    renderer->pointers->renderer_attach_another_window(
        renderer->backend,
        window->backend
    );
}

void Progator::Base::RendererUse(
    Progator::Base::Renderer* renderer
)
{
    renderer->pointers->renderer_use(
        renderer->backend
    );
}

void Progator::Base::RendererSetViewport(
    Progator::Base::Renderer* renderer,
    const Progator::Types::Specifics::Renderer::Viewport& viewport
)
{
    renderer->pointers->renderer_set_viewport(
        renderer->backend,
        viewport
    );
    renderer->viewport = viewport;
}

void Progator::Base::RendererAdjustVerticalSynchronization(
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::Boolean do_vsync
)
{
    renderer->pointers->renderer_adjust_vertical_synchronization(
        renderer->backend,
        do_vsync
    );
}

void Progator::Base::RendererClear(
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::U32 color
)
{
    renderer->pointers->renderer_clear(
        renderer->backend,
        color
    );
}

void Progator::Base::RendererDraw(
    Progator::Base::Renderer* renderer
)
{
    renderer->pointers->renderer_draw(
        renderer->backend
    );
}