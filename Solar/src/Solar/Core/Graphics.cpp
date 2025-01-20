#include "Solar/Core/Graphics.hpp"

Solar::Core::Graphics Solar::Core::GraphicsNew()
{
    Solar::Core::Graphics graphics;
    return graphics;
}

void Solar::Core::GraphicsDestroy(
    Solar::Core::Graphics* graphics
)
{
    /* Destroy Renderer: */
    Progator::Base::RendererDestroy(graphics->renderer);
    Progator::Base::WindowDestroy(graphics->window);
    Progator::Base::PointersDestroy(&graphics->pointers);
    Progator::Quit(&graphics->validator);
}

void Solar::Core::GraphicsInit(
    Solar::Core::Graphics* graphics
)
{
    /* Require the initialization of the SDL: */
    Progator::Init(&graphics->validator);

    /* Initialize the Pointers: */
    graphics->pointers = Progator::Base::PointersNew();
    Progator::Base::PointersInit(&graphics->pointers);
    
    /* TODO: on the future, enable API selection! */
    Progator::Base::PointersSetOpenGLMode(&graphics->pointers);

    /* Initialize the Window: */
    graphics->window = Progator::Base::WindowNew();
    Progator::Base::WindowInit(
        graphics->window,
        &graphics->pointers,
        &graphics->validator
    );
    
    /* Initialize the renderer */
    graphics->renderer = Progator::Base::RendererNew();
    Progator::Base::RendererInit(
        graphics->renderer,
        graphics->window,
        &graphics->pointers,
        &graphics->validator
    );
    Progator::Base::RendererSetViewport(
        graphics->renderer,
        {
            .width  = graphics->window->geometry.width,
            .height = graphics->window->geometry.height,
            .x      = 0,
            .y      = 0
        }
    );
    Progator::Base::RendererAdjustVerticalSynchronization(
        graphics->renderer,
        true
    );
}