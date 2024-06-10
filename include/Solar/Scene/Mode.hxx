#ifndef solar_scene_mode_hxx
#define solar_scene_mode_hxx

#include "Solar/Shapes/Plane.hxx"
#include "Solar/Shapes/Cube.hxx"
#include "Solar/Core/Shared.hxx"
#include "Solar/Scene/FreeCamera.hxx"

#include "Solar/GL.hxx"
#include "Solar/Types.hxx"
#include "Solar/Math/Vector3.hxx"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Solar
{
    namespace Scene
    {
        class Mode
        {
            public:
            Solar::Core::Shared         *linked_core;
            Solar::Shapes::Plane        baseplate;
            Solar::Shapes::Plane        baseplate_extra;
            Solar::Shapes::Cube         cube;
            Solar::Scene::FreeCamera    free_camera;

            glm::mat4 BasicPespectiveProjection;
            glm::mat4 BasicPespectiveView;

            Solar::Math::Vector3::D32 cam_position { 0, 0, 0 };
            Solar::Math::Vector3::D32 cam_rotation { 0, 0, 0 };
            
            void Init(Solar::Core::Shared *shared_core);
            void Quit();

            void UpdateTickUniformVariables();
            void ProcessEvents();
            void Tick();

            void UpdateDrawUniformVariables();
            void Draw();
        };
    };
};

#endif
// Solar/Scene/Mode.hxx: