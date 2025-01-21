#ifndef SolarModesSceneComponentsEvents_hpp
#define SolarModesSceneComponentsEvents_hpp

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            namespace Components
            {
                /// @brief an std::vector that holds all the events from a single instance.
                typedef std::vector<SDL_Event> Events;

                Solar::Modes::Scene::Components::Events EventsNew();
                void EventsDestroy(Solar::Modes::Scene::Components::Events* events);
                void EventsInit(Solar::Modes::Scene::Components::Events* events);
                void EventsGet(Solar::Modes::Scene::Components::Events* events);
            };
        };
    };
};

#endif