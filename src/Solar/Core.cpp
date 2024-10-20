#include "Solar/Core.hpp"

#include <iostream>

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
    
    /* NOTE: try to open the icon, if possible, then keep the icon: */
    Progator::WindowSetIcon(core->window, "./Root/WindowIcon.png");
    ProgatorHelperTreatErrorValidator(
        core->validator, 
        {
            std::cerr
                << core->validator->log
                << "\n";
        }
    );

    Progator::RendererSetViewport(core->renderer, 800, 640, 0, 0);
    Progator::RendererClear(core->renderer, 0x00000000);

    /* Initialize the provider: */
    core->provider = Solar::Engine::ProviderNew();
    Solar::Engine::ProviderInit(
        core->provider,
        Solar::Engine::ProviderProperties{.basepath="./Root/", .renderer="OpenGL"},
        core->pointers,
        core->validator
    );
}

void Solar::CoreQuit(Solar::Core* core)
{
    Progator::RendererDestroy(core->renderer);
    Progator::WindowDestroy(core->window);
    Progator::PointersDestroy(core->pointers);
    Progator::ValidatorDestroy(core->validator);
    Solar::Engine::ProviderDestroy(core->provider);
    Progator::Quit();
}
