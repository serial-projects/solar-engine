#ifndef SolarModesSceneLevelStructure_hpp
#define SolarModesSceneLevelStructure_hpp

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            struct Level
            {

            };
            Solar::Modes::Scene::Level* LevelNew();
            void LevelDestroy(Solar::Modes::Scene::Level* level);
            void LevelInit(Solar::Modes::Scene::Level* level);
            void LevelTick(Solar::Modes::Scene::Level* level);
            void LevelDraw(Solar::Modes::Scene::Level* level);
            void LevelQuit(Solar::Modes::Scene::Level* level);
        };
    };
};

#endif