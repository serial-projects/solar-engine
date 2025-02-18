#ifndef SolarModesSceneLevelRecipeLoad_hpp
#define SolarModesSceneLevelRecipeLoad_hpp

#include "Solar/Modes/Scene/Level/Recipe/Structure.hpp"
#include "Solar/Modes/Scene/Mode.hpp"
#include "Solar/Types.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            /// @brief This function will load an data file and load an recipe.
            /// @param recipe the recipe to be loaded.
            /// @param site the site that the recipe is.
            /// @param name the name of the recipe inside the recipe.
            void LevelRecipeLoad(
                Solar::Modes::Scene::LevelRecipe* recipe,
                Solar::Modes::Scene::Mode* mode,
                const Solar::Types::Basic::String& site,
                const Solar::Types::Basic::String& name
            );
        };
    };
};

#endif