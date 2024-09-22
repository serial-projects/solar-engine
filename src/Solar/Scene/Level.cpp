#include "Solar/Scene/Level.hpp"

Solar::Scene::Level* Solar::Scene::LevelNew()
{
    Solar::Scene::Level* proto = new Solar::Scene::Level;
    return proto;
}

void Solar::Scene::LevelDestroy(Solar::Scene::Level* level)
{
    delete level;
}

void Solar::Scene::LevelInit(Solar::Scene::Level* level, Solar::Core *core)
{
    level->linked_core = core;
    level->current_shader = Solar::Engine::ProviderLoadShader(level->linked_core->provider, "BasicView");
}

void Solar::Scene::LevelTick(Solar::Scene::Level* level)
{
    /* NOTE: Basic event handler: */
    SDL_Event os_event_handler;
    while(SDL_PollEvent(&os_event_handler))
    {
        switch(os_event_handler.type)
        {
            case SDL_QUIT:
                level->linked_core->state = 0;
                break;
            default:
                break;
        }
    }

    /* TODO: keep updating the scene: */
}

void Solar::Scene::LevelDraw(Solar::Scene::Level* level)
{
    /* TODO: implement should redraw to prevent drawing useless frames: */
    Progator::RendererClear(level->linked_core->renderer, 0x00000000);
    Progator::WindowDraw(level->linked_core->window);
}

void Solar::Scene::LevelQuit(Solar::Scene::Level* level)
{
    /* TODO: do saving and other crap here: */
}