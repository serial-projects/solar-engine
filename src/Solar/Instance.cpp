#include "Solar/Instance.hpp"

Solar::Instance* Solar::InstanceNew()
{
    Solar::Instance* proto = new Solar::Instance;
    return proto;
}

void Solar::InstanceDestroy(Solar::Instance* instance)
{
    Solar::CoreDestroy(instance->core);
    delete instance;
}

void Solar::InstanceInit(Solar::Instance* instance)
{
    instance->core = Solar::CoreNew();
    Solar::CoreInit(instance->core);

    /* set to init: */
    instance->core->state = 1;
}

static void BasicEventListener(Solar::Instance* instance)
{
    SDL_Event event_handler;
    while(SDL_PollEvent(&event_handler))
    {
        switch(event_handler.type)
        {
            case SDL_QUIT:
                instance->core->state = 0;
                break;
            default:
                break;
        }
    }
}

void Solar::InstanceTick(Solar::Instance* instance)
{
    BasicEventListener(instance);
}

void Solar::InstanceDraw(Solar::Instance* instance)
{
    Progator::RendererClear(instance->core->renderer, 0x00000000);
    /* BEGIN DRAW STACK: */
    
    /* END DRAW STACK: */
    Progator::WindowDraw(instance->core->window);
}

void Solar::InstanceQuit(Solar::Instance* instance)
{
    Solar::CoreQuit(instance->core);
}

void Solar::InstanceLoop(Solar::Instance* instance)
{
    while(instance->core->state)
    {
        Solar::InstanceTick(instance);
        Solar::InstanceDraw(instance);
    }
}