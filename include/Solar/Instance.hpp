#ifndef SolarInstance_hpp
#define SolarInstance_hpp

#include "Solar/Types.hpp"
#include "Solar/Core.hpp"

#include "Solar/Scene/Mode.hpp"

namespace Solar
{
    typedef struct Instance
    {
        Solar::Core* core;
        Solar::Scene::Mode* scene_mode;
    } Instance;
    
    Solar::Instance* InstanceNew();
    void InstanceDestroy(Solar::Instance* instance);
    void InstanceInit(Solar::Instance* instance);
    void InstanceTick(Solar::Instance* instance);
    void InstanceDraw(Solar::Instance* instance);
    void InstanceQuit(Solar::Instance* instance);
    void InstanceLoop(Solar::Instance* instance);

    /* MODES: */
    enum InstanceModes
    {
        QUIT        = 0,
        SCENE,
        OPTIONS,
        LOADING
    };
};

#endif