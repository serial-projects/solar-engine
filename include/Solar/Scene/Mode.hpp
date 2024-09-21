#ifndef SolarSceneMode_hpp
#define SolarSceneMode_hpp

#include "Solar/Types.hpp"
#include "Solar/Core.hpp"

#include "Solar/Scene/Level.hpp"

namespace Solar
{
    namespace Scene
    {
        /* MODE: In simple words, the scene mode holds all the scenes, this allows for better
         * flexibility on Instance that can change from scene mode to something else.
         */
        typedef struct Mode
        {
            Solar::Core *linked_core;
            Solar::Scene::Level* current_level;
        } Mode;
        
        Solar::Scene::Mode* ModeNew();
        void ModeDestroy(Solar::Scene::Mode* mode);
        void ModeInit(Solar::Scene::Mode* mode, Solar::Core *core);
        void ModeTick(Solar::Scene::Mode* mode);
        void ModeDraw(Solar::Scene::Mode* mode);
        void ModeQuit(Solar::Scene::Mode* mode);
    };
};

#endif