#include "Solar/Instance.hpp"

/*
 * InstanceNew():
 */

Solar::Instance* Solar::InstanceNew()
{
    Solar::Instance* proto = new Solar::Instance;
    return proto;
}

/*
 * InstanceDestroy():
 */

void Solar::InstanceDestroy(Solar::Instance* instance)
{
    Solar::Scene::ModeDestroy(instance->scene_mode);
    Solar::CoreDestroy(instance->core);
    delete instance;
}

/* 
 * InstanceInit():
 */

void Solar::InstanceInit(Solar::Instance* instance)
{
    /* initialize the core: */
    instance->core = Solar::CoreNew();
    Solar::CoreInit(instance->core);

    /* initialize the scene mode: */
    instance->scene_mode = Solar::Scene::ModeNew();
    Solar::Scene::ModeInit(instance->scene_mode, instance->core);

    /* set to init: */
    instance->core->state = 1;
}

/*
 * InstanceTick():
 */

void Solar::InstanceTick(Solar::Instance* instance)
{
    switch(instance->core->state)
    {
        case Solar::InstanceModes::SCENE:
            Solar::Scene::ModeTick(instance->scene_mode);
            break;
        default:
            break;
    }
}

/*
 * InstanceDraw():
 */

void Solar::InstanceDraw(Solar::Instance* instance)
{
    switch(instance->core->state)
    {
        case Solar::InstanceModes::SCENE:
            Solar::Scene::ModeDraw(instance->scene_mode);
            break;
        default:
            break;
    }
}

/*
 * InstanceQuit():
 */

void Solar::InstanceQuit(Solar::Instance* instance)
{
    Solar::Scene::ModeQuit(instance->scene_mode);
    Solar::CoreQuit(instance->core);
}

/*
 * InstanceLoop():
 */

void Solar::InstanceLoop(Solar::Instance* instance)
{
    while(instance->core->state)
    {
        Solar::InstanceTick(instance);
        Solar::InstanceDraw(instance);
    }
}