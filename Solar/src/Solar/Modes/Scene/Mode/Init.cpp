#include "Solar/Modes/Scene/Mode/Init.hpp"

void Solar::Modes::Scene::ModeInit(
    Solar::Modes::Scene::Mode* mode,
    Solar::Core::Shared* shared
)
{
    mode->events = Solar::Modes::Scene::Components::EventsNew();
    Solar::Modes::Scene::Components::EventsInit(&mode->events);
    mode->shared = shared;
}