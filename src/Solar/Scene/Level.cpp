#include "Solar/Scene/Level.hpp"
#include "Solar/Scene/Shapes.hpp"

/* NOTE: Solar Engine is a VOXEL based RPG engine, it has support for 3D but everything must be
 * inside an cell and the camera is always on the top.
 */

Solar::Scene::Level* Solar::Scene::LevelNew()
{
    Solar::Scene::Level* proto = new Solar::Scene::Level;
    return proto;
}

void Solar::Scene::LevelDestroy(Solar::Scene::Level* level)
{
    delete level;
}

/*
 * INIT:
 */

void Solar::Scene::LevelInit(Solar::Scene::Level* level, Solar::Core *core)
{
    level->linked_core = core;

    /* Create the cameras: */
    level->camera = Solar::Scene::FreeCameraNew();
    
    /* Initialize the basic voxels: */
    level->basic_voxel_shader = Solar::Engine::ProviderLoadShader(level->linked_core->provider, "BasicVoxels");
    level->basic_voxel_mesh = Progator::MeshNew();
    Progator::MeshInit(level->basic_voxel_mesh, level->linked_core->pointers, level->linked_core->validator);
    Progator::MeshLoadVerTexNor(level->basic_voxel_mesh, Solar::Scene::Shapes::CubeWithVertexTextureMapAndNormals, 6 * 6);
}

/* TICK: */
static void UpdateCurrentShaderUniforms(Solar::Scene::Level* level)
{
    /* SolarProjectionMatrix:             (mat4): */
    const Progator::Matrix44 projection = glm::perspective(
        45.0f   ,
        ((float)level->linked_core->renderer->width/(float)level->linked_core->renderer->height),
        0.1f    ,
        256.0f
    );
    Progator::ShaderSUMatrix44(level->basic_voxel_shader, "SolarProjectionMatrix", projection);

    /* SolarViewMatrix:                   (mat4): */
    const Progator::Matrix44 view = Solar::Scene::FreeCameraGetViewMatrix(&level->camera);
    Progator::ShaderSUMatrix44(level->basic_voxel_shader, "SolarViewMatrix", view);
}

static void TickProcessEngineInternalKeydowns(Solar::Scene::Level* level, SDL_Keysym* keysym)
{
    switch(keysym->scancode)
    {
        case SDL_SCANCODE_F1:
            level->debug_states ^= (1 << (8 - 1));
            glPolygonMode( GL_FRONT_AND_BACK, (level->debug_states & Solar::Scene::LevelDebugStates::WireframeMode ? GL_LINE : GL_FILL) );
            break;
        default:
            break;
    };
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
            case SDL_MOUSEMOTION:
                /* TODO: this is only on free mode camera: */
                Solar::Scene::FreeCameraSetLooking(
                    &level->camera,
                    os_event_handler.motion.xrel,
                    -os_event_handler.motion.yrel
                );
                break;
            case SDL_KEYDOWN:
                /* HANDLE THE KEYDOWN: */
                {
                    SDL_Keysym* keysym = &os_event_handler.key.keysym;
                    TickProcessEngineInternalKeydowns(level, keysym);
                };
            default:
                break;
        }
    }

    /* NOTE: keyboard input: */
    const Solar::U8* keyboard = SDL_GetKeyboardState(NULL);
    if(keyboard[SDL_SCANCODE_W]) Solar::Scene::FreeCameraSetPosition(&level->camera, 0);
    if(keyboard[SDL_SCANCODE_S]) Solar::Scene::FreeCameraSetPosition(&level->camera, 1);
    if(keyboard[SDL_SCANCODE_A]) Solar::Scene::FreeCameraSetPosition(&level->camera, 2);
    if(keyboard[SDL_SCANCODE_D]) Solar::Scene::FreeCameraSetPosition(&level->camera, 3);

    /* TODO: keep updating the scene: */
    UpdateCurrentShaderUniforms(level);
}

static void DrawVoxel(Solar::Scene::Level* level, Solar::Vector3 position)
{
    /* SolarModelMatrix:              (mat4): */
    Progator::Matrix44 model    = glm::mat4(1.0f);
    model                       = glm::translate(model, position);
    model                       = glm::scale(model, Progator::Vector3(1.0f, 1.0f, 1.0f));
    Progator::ShaderSUMatrix44(level->basic_voxel_shader, "SolarModelMatrix", model);

    /* Draw the mesh: */
    Progator::MeshDraw(level->basic_voxel_mesh);
}

void Solar::Scene::LevelDraw(Solar::Scene::Level* level)
{
    /* TODO: implement should redraw to prevent drawing useless frames: */
    Progator::RendererClear(level->linked_core->renderer, 0x00000000);
    
    /* NOTE: this the root node and it is always located on the center of the level.
     * and has no other purpose but to debug where the level is located on:
     */
    Progator::ShaderUse(level->basic_voxel_shader);
    DrawVoxel(level, Solar::Vector3(0.0f, 0.0f, 0.0f));

    Progator::WindowDraw(level->linked_core->window);
}

void Solar::Scene::LevelQuit(Solar::Scene::Level* level)
{
    /* TODO: do saving and other crap here: */
}