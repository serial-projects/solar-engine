#include "Solar/Modes/Scene/Components/Events.hpp"
#include "Solar/Config.hpp"

Solar::Modes::Scene::Components::Events Solar::Modes::Scene::Components::EventsNew()
{
    Solar::Modes::Scene::Components::Events events;
    return events;
}

void Solar::Modes::Scene::Components::EventsDestroy(
    Solar::Modes::Scene::Components::Events* events
)
{
    /* NOTE: do nothing, events on the stack. */
    return;
}

void Solar::Modes::Scene::Components::EventsInit(
    Solar::Modes::Scene::Components::Events* events
)
{
    events->reserve(
        SOLAR_MODES_SCENE_COMPONENTS_EVENTS_SIZE
    );
}

void Solar::Modes::Scene::Components::EventsGet(
    Solar::Modes::Scene::Components::Events* events
)
{
    events->clear();

    /* keep getting the new events: */
    SDL_Event event;
    while(SDL_PollEvent(&event) && events->size() < SOLAR_MODES_SCENE_COMPONENTS_EVENTS_SIZE)
        events->push_back(event);
}