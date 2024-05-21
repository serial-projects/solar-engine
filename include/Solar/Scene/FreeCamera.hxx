#ifndef solar_scene_freecamera_hxx
#define solar_scene_freecamera_hxx

// NOTE: this code is based from https://learnopengl.com/Getting-started/Camera
// But here there is no implementation of ZOOM, since it is not needed.

#include "Solar/Types.hxx"
#include "Solar/GL.hxx"
#include "Solar/Core/Shared.hxx"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Solar
{
    namespace Scene
    {
        enum FreeCameraMovementDirections
        {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };
        class FreeCamera
        {
            public:
            glm::vec3 position;
            glm::vec3 front;
            glm::vec3 up;   
            glm::vec3 right; 
            glm::vec3 worldup;
            
            Solar::Types::D32 yaw           = -90.0f;
            Solar::Types::D32 pitch         = 0.0f;
            Solar::Types::D32 speed         = 2.5f;
            Solar::Types::D32 sensitivity   = 0.1f;

            // NOTE: mouse offset is calculated here:
            Solar::Types::D32 last_mouse_x = 0.0f;
            Solar::Types::D32 last_mouse_y = 0.0f;

            // Init
            void Init(Solar::Core::Shared *shared_core);
            void Quit();

            glm::mat4 GetViewMatrix();
            void UpdateCameraVectors();

            // Adapt for SDL2:
            void ProcessMouse(const Solar::Types::I8 xoffset, const Solar::Types::I8 yoffset);
            void ProcessKeyboard();

            // NOTE: here we don't need the constraint variable, this is present
            // on the original code, but here, the camera is always constrained.
            void Rotate(Solar::Types::D32 xoff, Solar::Types::D32 yoff);

            // NOTE (2): here there is no delta time here:
            void Move(Solar::Scene::FreeCameraMovementDirections direction);
        };
    };
};

#endif
// Solar/Scene/FreeCamera.hxx: