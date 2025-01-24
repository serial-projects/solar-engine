#ifndef SolarModesSceneModeInit_hpp
#define SolarModesSceneModeInit_hpp

#include "Solar/Modes/Scene/Mode/Structure.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            /// @brief initializes an scene mode.
            /// @param mode the mode to be initialized.
            /// @param shared the shared core.
            void ModeInit(Solar::Modes::Scene::Mode* mode, Solar::Core::Shared* shared);
        };
    };
};

#endif