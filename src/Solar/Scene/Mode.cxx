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

    this->baseplate.position.x = 0;
    this->baseplate.position.y = 20;
    this->baseplate.position.z = 0;

    this->baseplate_extra.position.x = 0;
    this->baseplate_extra.position.y = 20;
    this->baseplate_extra.position.z = 0;

    this->cube.size.x = 80;
    this->cube.size.z = 80;
    this->cube.size.y = 10;
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
                WHEN(evh.key.keysym.scancode == SDL_SCANCODE_ESCAPE, this->linked_core->mode = 0);
                WHEN(evh.key.keysym.scancode == SDL_SCANCODE_F1, glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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