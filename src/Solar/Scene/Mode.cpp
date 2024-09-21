#include "Solar/Scene/Mode.hpp"

Solar::Scene::Mode* Solar::Scene::ModeNew()
{
    Solar::Scene::Mode* proto = new Solar::Scene::Mode;
    return proto;
}

void Solar::Scene::ModeDestroy(Solar::Scene::Mode* mode)
{
    /* NOTE: delete all the loaded levels: */
    Solar::Scene::LevelDestroy(mode->current_level);

    delete mode;
}

void Solar::Scene::ModeInit(Solar::Scene::Mode* mode, Solar::Core *core)
{
    mode->linked_core = core;
    
    mode->current_level = Solar::Scene::LevelNew();
    Solar::Scene::LevelInit(mode->current_level, mode->linked_core);
}

void Solar::Scene::ModeTick(Solar::Scene::Mode* mode)
{
    Solar::Scene::LevelTick(mode->current_level);
}

void Solar::Scene::ModeDraw(Solar::Scene::Mode* mode)
{
    Solar::Scene::LevelDraw(mode->current_level);
}

void Solar::Scene::ModeQuit(Solar::Scene::Mode* mode)
{
    Solar::Scene::LevelQuit(mode->current_level);
}