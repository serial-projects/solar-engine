#include "Solar/Core.hpp"

Solar::Core* Solar::CoreNew()
{
    Solar::Core* proto = new Solar::Core;
    return proto;
}

void Solar::CoreDestroy(Solar::Core* core)
{
    delete core;
}

void Solar::CoreInit(Solar::Core* core)
{
    /* dynamically allocate these objects: */
    core->validator = Progator::ValidatorNew();
    core->pointers  = Progator::PointersNew();
    core->window    = Progator::WindowNew();
    core->renderer  = Progator::RendererNew();

    /* initialize Progator subsystems: */
    Progator::Init(core->validator);

    /* begin initializing everything: */
    Progator::PointersUseOpenGLBackend(core->pointers);
    Progator::WindowInit(core->window, core->pointers, core->validator);
    Progator::RendererInit(core->renderer, core->pointers, core->validator);

    /* Load the initial game settings... */
    Progator::WindowSetSize(core->window, 800, 640);
    Progator::WindowSetTitle(core->window, "[Solar Engine]");
    Progator::WindowSetVerticalSync(core->window, PROGATOR_YES);
    Progator::RendererSetViewport(core->renderer, 800, 640, 0, 0);
    Progator::RendererClear(core->renderer, 0x00000000);
}

void Solar::CoreQuit(Solar::Core* core)
{
    Progator::RendererDestroy(core->renderer);
    Progator::WindowDestroy(core->window);
    Progator::PointersDestroy(core->pointers);
    Progator::ValidatorDestroy(core->validator);
    Progator::Quit();
}
