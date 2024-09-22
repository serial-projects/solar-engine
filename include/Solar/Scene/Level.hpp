#ifndef SolarSceneLevel_hpp
#define SolarSceneLevel_hpp

#include "Solar/Types.hpp"
#include "Solar/Core.hpp"

#include "Solar/Scene/Camera.hpp"
#include "Solar/Scene/Level.hpp"

#include "Progator/Progator.hpp"

namespace Solar
{
    namespace Scene
    {
        namespace LevelProperties
        {
            /* TODO: implement this: */
        };

        typedef struct Level
        {
            Solar::Core* linked_core;
            Progator::Shader* current_shader;
        } Level;

        Solar::Scene::Level* LevelNew();
        void LevelDestroy(Solar::Scene::Level* level);
        void LevelInit(Solar::Scene::Level* level, Solar::Core *core);
        void LevelTick(Solar::Scene::Level* level);
        void LevelDraw(Solar::Scene::Level* level);
        void LevelQuit(Solar::Scene::Level* level);
    };
};

#endif