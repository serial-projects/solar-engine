#ifndef SolarModesSceneStructure_hpp
#define SolarModesSceneStructure_hpp

#include "Solar/Types.hpp"
#include "Solar/Core.hpp"
#include "Solar/Modes/Scene/Components/Events.hpp"

namespace Solar
{
    namespace Modes
    {
        /// @brief contains all the scene mode here, things such as level, current level, etc.
        namespace Scene
        {
            struct Mode
            {
                Solar::Core::Shared* shared;
                Solar::Modes::Scene::Components::Events events;
            };
            
            Solar::Modes::Scene::Mode ModeNew();
            void ModeDestroy(Solar::Modes::Scene::Mode* scene);
        };
    };
};

#endif