#ifndef SolarModesSceneLevelObjectsStructure_hpp
#define SolarModesSceneLevelObjectsStructure_hpp

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            struct LevelObject
            {
                Solar::Types::GLM::Vector3      position;
                Solar::Types::GLM::Vector3      size;
                Solar::Types::Basic::U16        recipe;
            };
            Solar::Modes::Scene::LevelObject* LevelObjectNew();
            void LevelObjectDestroy(Solar::Modes::Scene::LevelObject* object);
            void LevelObjectInit(Solar::Modes::Scene::LevelObject* object);
        };
    };
};

#endif