#include "Solar/Modes/Scene/Mode/Init.hpp"
#include "Solar/Modes/Scene/Pipelines/Init/LoadSettings.hpp"
#include "Solar/Modes/Scene/Pipelines/Init/LoadStory.hpp"

void Solar::Modes::Scene::ModeInit(
    Solar::Modes::Scene::Mode* mode,
    Solar::Core::Shared* shared
)
{
    mode->events = Solar::Modes::Scene::Components::EventsNew();
    mode->shared = shared;

    /* Init the internal events */
    Solar::Modes::Scene::Components::EventsInit(&mode->events);

    /* Begin the Init pipeline for the scene mode (the scene mode is initialized once only per
     * instance, meaning this functions will probably run a single time). */
    Solar::Modes::Scene::Pipelines::Init::LoadSettings(mode);
    Solar::Modes::Scene::Pipelines::Init::LoadStory(mode);
}