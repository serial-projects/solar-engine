#include "Solar/Scene/Mode.hxx"
#include "Solar/Utils.hxx"

#include <cmath>

void Solar::Scene::Mode::Init(Solar::Core::Shared *shared_core)
{
    // link the core:
    this->linked_core = shared_core;

    // initialize baseplate:
    this->baseplate.Init();
    this->baseplate_extra.Init();
    this->cube.Init();
    
    this->free_camera.Init(this->linked_core);
    this->free_camera.position.y = 10;

    // NOTE: for this mode, enable some OpenGL parameters:
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    
    // Set the current viewing port:
    glViewport(0, 0, this->linked_core->window.width, this->linked_core->window.height);

    // Setup the pespective (which is going to be moved for the camera)!
    this->BasicPespectiveProjection = glm::perspective(
        glm::radians(55.0f),
        (float)this->linked_core->window.width / (float)this->linked_core->window.height,
        0.1f,
        150.0f
    );

    this->baseplate.position.x  = 0;
    this->baseplate.position.y  = 20;
    this->baseplate.position.z  = 0;

    this->baseplate_extra.color.r     = 0xFF;
    this->baseplate_extra.color.g     = 0xEF;
    this->baseplate_extra.color.b     = 0xCF;
    this->baseplate_extra.color.a     = 0xFF;

    this->baseplate_extra.size.x = 10;
    this->baseplate_extra.size.y = 10;
    this->baseplate_extra.size.z = 10;

    this->baseplate_extra.position.x = 0;
    this->baseplate_extra.position.y = 0;
    this->baseplate_extra.position.z = 0;

    // 235, 64, 52
    this->cube.size.x   = 10;
    this->cube.size.z   = 10;
    this->cube.size.y   = 10;

    this->cube.position.x = 10;
    this->cube.position.y = 0;
    this->cube.position.z = 0;

    this->cube.color.r  = 235;
    this->cube.color.g  = 64;
    this->cube.color.b  = 52;

}

void SolarSceneMode_HandleKeyEvents(Solar::Scene::Mode *scene_mode, SDL_Keysym sym)
{
    const Solar::Types::U8 *keyboard_state = SDL_GetKeyboardState(NULL);
    const Solar::Types::Boolean has_shift_modifier = keyboard_state[SDL_SCANCODE_LSHIFT];
    WHEN(
        sym.scancode == SDL_SCANCODE_ESCAPE,
        {
            SolarCoreSharedMode_Shutdown(scene_mode->linked_core->mode);
        }
    );
    WHEN(
        sym.scancode == SDL_SCANCODE_F5,
        {
            SolarCoreSharedMode_ToggleDebug(scene_mode->linked_core->mode);
            WHEN(has_shift_modifier, {
                SolarCoreSharedMode_ToggleGDebug(scene_mode->linked_core->mode);
                glPolygonMode(GL_FRONT_AND_BACK, SolarCoreSharedMode_GetGDebug(scene_mode->linked_core->mode) ? GL_LINE : GL_FILL); 
            });
        }
    );
}

void Solar::Scene::Mode::ProcessEvents()
{
    SDL_Event evh;
    while(SDL_PollEvent(&evh))
    {
        switch(evh.type)
        {
            case SDL_QUIT:
                this->linked_core->mode = 0;
                break;
            case SDL_KEYDOWN:
                SolarSceneMode_HandleKeyEvents(this, evh.key.keysym);
                break;
            case SDL_MOUSEMOTION:
                this->free_camera.ProcessMouse((Solar::Types::I8)evh.motion.xrel,(Solar::Types::I8)evh.motion.yrel);
                break;
        }
    }
}

void Solar::Scene::Mode::UpdateTickUniformVariables()
{
    Solar::Core::Storage::Shader *using_shader = this->linked_core->content_provider.GetShader("Default");
    
    // SE_TickCounter:              number
    using_shader->SetIntegerUniform("SE_TickCounter", this->linked_core->tick_counter);
    
    // SE_ProjectionMatrix:         mat4
    using_shader->SetMatrixFourUniform("SE_ProjectionMatrix", this->BasicPespectiveProjection);
}

void Solar::Scene::Mode::Tick()
{
    // Begin by doing some basic events:
    this->ProcessEvents();
    this->free_camera.ProcessKeyboard();

    // Update the current shader uniforms:
    this->UpdateTickUniformVariables();
}

void Solar::Scene::Mode::UpdateDrawUniformVariables()
{
    Solar::Core::Storage::Shader *using_shader = this->linked_core->content_provider.GetShader("Default");

    // SE_ViewMatrix:               mat4
    using_shader->SetMatrixFourUniform("SE_ViewMatrix", this->BasicPespectiveView);
}

void Solar::Scene::Mode::Draw()
{
    // NOTE: set the skybox color (basic):
    glClearColor(0.05f, 0.01f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Clear the depth test:
    glClear(GL_DEPTH_BUFFER_BIT);

    // Set the view (aka. OpenGL's camera):
    this->BasicPespectiveView = this->free_camera.GetViewMatrix();

    // Update:
    this->UpdateDrawUniformVariables();

    // begin drawing the baseplate:
    Solar::Core::Storage::Shader *using_shader = this->linked_core->content_provider.GetShader("Default");
    this->baseplate.Draw(using_shader);
    this->baseplate_extra.Draw(using_shader);
    this->cube.Draw(using_shader);
}

void Solar::Scene::Mode::Quit()
{
    // Quit the camera!
    this->free_camera.Quit();

    // Some testing stuff:
    this->baseplate.Destroy();
    this->baseplate_extra.Destroy();
    this->cube.Destroy();
}