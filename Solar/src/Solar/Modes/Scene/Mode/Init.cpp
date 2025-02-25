#include "Solar/Modes/Scene/Mode/Init.hpp"
#include "Solar/Modes/Scene/Mode/Pipelines/Init/LoadSettings.hpp"
#include "Solar/Modes/Scene/Mode/Pipelines/Init/LoadStory.hpp"

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
    Solar::Modes::Scene::ModePipelines::Init::LoadSettings(mode);
    Solar::Modes::Scene::ModePipelines::Init::LoadStory(mode);

    /* Test shader: */
    Solar::Core::Provider::Load::Shader(
        &mode->shared->warehouse,
        "root:Shaders/Basic",
        "main"
    );

    Solar::Core::Provider::Load::Mesh(
        &mode->shared->warehouse,
        "root:Meshes/Cube",
        "Cube.*",
        "main"
    );
}