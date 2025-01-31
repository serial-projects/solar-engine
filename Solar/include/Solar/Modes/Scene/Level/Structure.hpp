#ifndef SolarModesSceneLevelStructure_hpp
#define SolarModesSceneLevelStructure_hpp

#include "Solar/Modes/Scene/Mode/Structure.hpp"
#include "Solar/Types.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            struct Level
            {
                Solar::Types::Basic::String name;
            };
            Solar::Modes::Scene::Level* LevelNew();
            void LevelDestroy(Solar::Modes::Scene::Level* level);
        };
    };
};

#endif