#include "Solar/Modes/Scene/Mode/Tick.hpp"

void Solar::Modes::Scene::ModeTick(
    Solar::Modes::Scene::Mode* mode
)
{
    /* First stage: GetEvents */
    Solar::Modes::Scene::Components::EventsGet(&mode->events);

    /* Second Stage: Basic Events (SDL_Quit and etc.): */
    for(auto &event : mode->events)
    {
        switch(event.type)
        {
            case SDL_QUIT:
                mode->shared->basics.state = 0;
                break;
        };
    }
}