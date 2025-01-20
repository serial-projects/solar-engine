#ifndef SolarInstanceStructure_hpp
#define SolarInstanceStructure_hpp

#include "Solar/Core.hpp"

namespace Solar
{
    /// @brief Contains the whole game instance with core, etc.
    struct Instance
    {
        /// @brief This is the core that is to be shared all around, contains everything to the
        /// instance, state, renderer and etc.
        Solar::Core::Shared     shared_core;
    };

    Solar::Instance InstanceNew();
    void InstanceDestroy(Solar::Instance* instance);
};

#endif