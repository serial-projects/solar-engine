#include "Solar/Instance/Tick.hpp"

void Solar::InstanceTick(
    Solar::Instance* instance
)
{
    /* Pump the events: */
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                instance->shared_core.basics.state = 0;
                break;
        };
    }
}