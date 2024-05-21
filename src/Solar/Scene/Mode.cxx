#include "Solar/Scene/Mode.hxx"
#include "Solar/Utils.hxx"

#include <cmath>

namespace Solar
{
    namespace Scene
    {
        void Mode::Init(Solar::Core::Shared *shared_core)
        {
            // link the core:
            this->linked_core = shared_core;

            // initialize baseplate:
            this->baseplate.Init();
            this->baseplate_extra.Init();
            this->cube.Init();
            
            this->camera.Init(this->linked_core);
            this->camera.position.y = 10;

            // NOTE: for this mode, enable some OpenGL parameters:
            glEnable(GL_DEPTH_TEST);

            // Set the current viewing port:
            glViewport(0, 0, this->linked_core->window.width, this->linked_core->window.height);

            // Setup the pespective (which is going to be moved for the camera)!
            this->BasicPespectiveProjection = glm::perspective(
                glm::radians(55.0f),
                (float)this->linked_core->window.width / (float)this->linked_core->window.height,
                0.1f,
                150.0f
            );

            // set the view to the position!
            this->BasicPespectiveView = glm::mat4(1.0f);
            this->BasicPespectiveView = glm::translate(this->BasicPespectiveView, glm::vec3(0.0f, 0.0f, -3.0f));

            this->baseplate.position.x = 0;
            this->baseplate.position.y = 20;
            this->baseplate.position.z = 0;

            this->baseplate_extra.position.x = 0;
            this->baseplate_extra.position.y = 20;
            this->baseplate_extra.position.z = 0;
        }

        void Mode::ProcessEvents()
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
                        this->camera.ProcessMouse((Solar::Types::I8)evh.motion.xrel,(Solar::Types::I8)evh.motion.yrel);
                        break;
                }
            }
        }

        void Mode::Tick()
        {
            // Begin by doing some basic events:
            this->ProcessEvents();
            this->camera.ProcessKeyboard();

            // Update the current shader uniforms:
            this->linked_core->content_provider.GetShader("Default")->SetIntegerUniform(
                "SolarTickCounter",
                this->linked_core->tick_counter
            );

            //this->baseplate.position.x = 10 % (this->linked_core->tick_counter / 60);
            this->baseplate.rotation.x = (this->linked_core->tick_counter);
            this->baseplate.rotation.y = (this->linked_core->tick_counter * 2);
            this->baseplate.rotation.z = (this->linked_core->tick_counter * 2.5);
            
            this->baseplate_extra.rotation.x = (this->linked_core->tick_counter * 2.5);
            this->baseplate_extra.rotation.y = (this->linked_core->tick_counter * 2);
            this->baseplate_extra.rotation.z = (this->linked_core->tick_counter);

            this->cube.size.x = 80;
            this->cube.size.y = 1;
            this->cube.size.z = 80;
            this->cube.rotation.y = (this->linked_core->tick_counter / 15);

            // this->cube.rotation.x = (this->linked_core->tick_counter);
            // this->cube.rotation.y = (this->linked_core->tick_counter * 2);
            // this->cube.rotation.z = (this->linked_core->tick_counter * 2.5);
        }
        void Mode::Draw()
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Set the view (aka. OpenGL's camera):
            this->BasicPespectiveView = this->camera.GetViewMatrix();

            // this->BasicPespectiveView = glm::translate(glm::mat4(1.0f), this->cam_position.ToGLM());
            // this->BasicPespectiveView = glm::rotate(this->BasicPespectiveView, glm::radians(this->cam_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            // this->BasicPespectiveView = glm::rotate(this->BasicPespectiveView, glm::radians(this->cam_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            // this->BasicPespectiveView = glm::rotate(this->BasicPespectiveView, glm::radians(this->cam_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

            // begin drawing the baseplate:
            Solar::Core::Storage::Shader *using_shader = this->linked_core->content_provider.GetShader("Default");
            using_shader->SetMatrixFourUniform("SolarCurrentRenderingProjectionMatrix", this->BasicPespectiveProjection);
            using_shader->SetMatrixFourUniform("SolarCurrentRenderingViewMatrix", this->BasicPespectiveView);
            
            this->baseplate.Draw(using_shader);
            this->baseplate_extra.Draw(using_shader);
            this->cube.Draw(using_shader);
        }
        void Mode::Quit()
        {
            // Quit the camera!
            this->camera.Quit();

            // Some testing stuff:
            this->baseplate.Destroy();
            this->baseplate_extra.Destroy();
            this->cube.Destroy();
        }
    };
};