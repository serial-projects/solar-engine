#ifndef SolarInstanceStructure_hpp
#define SolarInstanceStructure_hpp

#include "Solar/Core.hpp"

namespace Solar
{
    struct Instance
    {
        /// @brief This is the core that is to be shared all around, contains everything to the
        /// instance, state, renderer and etc.
        Solar::Core::Shared     shared_core;
    };

    Solar::Instance InstanceNew();
    void InstanceDestroy(Solar::Instance* instance);
    void InstanceInit(Solar::Instance* instance);
    void InstanceTick(Solar::Instance* instance);
    void InstanceDraw(Solar::Instance* instance);
    void InstanceLoop(Solar::Instance* instance);
    void InstanceQuit(Solar::Instance* instance);
};

#endif