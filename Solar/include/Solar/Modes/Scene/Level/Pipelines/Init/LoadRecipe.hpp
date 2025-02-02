#ifndef SolarModesSceneLevelPipelinesInitLoadRecipe_hpp
#define SolarModesSceneLevelPipelinesInitLoadRecipe_hpp

#include "Solar/Modes/Scene/Level/Structure.hpp"
#include "Solar/Types.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            namespace LevelPipelines
            {
                namespace Init
                {
                    /// @brief Loads the recipe to cache.
                    /// @param level the level to the loaded.
                    /// @param mode the mode attached to the level.
                    /// @param world_key the key of the world to be loaded.
                    void LoadRecipe(
                        Solar::Modes::Scene::Level* level,
                        Solar::Modes::Scene::Mode* mode,
                        const Solar::Types::Basic::String& world_key
                    );
                };
            };
        };
    };
};

#endif