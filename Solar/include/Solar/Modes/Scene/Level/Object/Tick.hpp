#ifndef SolarModesSceneLevelObjectsTick_hpp
#define SolarModesSceneLevelObjectsTick_hpp

#include "Solar/Modes/Scene/Mode/Structure.hpp"
#include "Solar/Modes/Scene/Level/Object/Structure.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            void LevelObjectTick(
                Solar::Modes::Scene::LevelObject* object,
                Solar::Modes::Scene::Mode* mode
            );
        };
    };
};

#endif