#ifndef SolarInstance_hpp
#define SolarInstance_hpp

#include "Solar/Types.hpp"
#include "Solar/Core.hpp"

namespace Solar
{
    typedef struct Instance
    {
        Solar::Core* core;
    } Instance;
    
    Solar::Instance* InstanceNew();
    void InstanceDestroy(Solar::Instance* instance);
    void InstanceInit(Solar::Instance* instance);
    void InstanceTick(Solar::Instance* instance);
    void InstanceDraw(Solar::Instance* instance);
    void InstanceQuit(Solar::Instance* instance);
    void InstanceLoop(Solar::Instance* instance);
};

#endif