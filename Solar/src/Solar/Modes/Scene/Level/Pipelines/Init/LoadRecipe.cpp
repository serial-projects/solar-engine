#include "Solar/Modes/Scene/Level/Pipelines/Init/LoadRecipe.hpp"
#include "Solar/Core/Provider.hpp"

/*
 * NOTE: an Solar World consists on:
 * Layers.jsonc:        contains the layers of the world.
 * Level.jsonc:         contains the world information.
 * 
 * Expected = root:World/Room00/
 *      -> root:World/Room00(/Level.jsonc)          [REQUIRED]
 *      -> root:World/Room00(/Layers.jsonc)         [REQUIRED]
 */

void Solar::Modes::Scene::LevelPipelines::Init::LoadRecipe(
    Solar::Modes::Scene::Level* level,
    Solar::Modes::Scene::Mode* mode,
    const Solar::Types::Basic::String& world_key
)
{
    /* load the Level.jsonc file: */
    Solar::Core::Provider::Load::DataFile(
        &mode->shared->warehouse,
        world_key + "/Level"
    );

    /* load the Layers.jsonc file: */
    Solar::Core::Provider::Load::DataFile(
        &mode->shared->warehouse,
        world_key + "Layers"
    );
}