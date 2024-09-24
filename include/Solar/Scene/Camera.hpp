#ifndef SolarSceneCamera_hpp
#define SolarSceneCamera_hpp

#include "Solar/Types.hpp"
#include "Progator/Progator.hpp"

namespace Solar
{
    namespace Scene
    {
        namespace Properties
        {
            typedef struct FreeCamera
            {
                
            } FreeCamera;
        };

        typedef struct FreeCamera
        {
            /* NOTE: this will generate our matrix on the future: */
            Solar::Vector3  position            = glm::vec3(0.0f, 0.0f, 0.0f    );
            Solar::Vector3  front               = glm::vec3(0.0f, 0.0f, -1.0f   );
            Solar::Vector3  up                  = glm::vec3(0.0f);
            Solar::Vector3  right               = glm::vec3(0.0f);
            Solar::Vector3  world_up            = glm::vec3(0.0f, 1.0f, 0.0f    );
            
            /* This is the orientation: */
            Solar::F32      yaw                 = -90.0f;
            Solar::F32      pitch               = 0.0f;
            Solar::F32      mov_speed           = 0.1f;
            Solar::F32      mov_sensitivity     = 0.3f;
        } FreeCamera;

        Solar::Scene::FreeCamera FreeCameraNew();
        Solar::Matrix44 FreeCameraGetViewMatrix(Solar::Scene::FreeCamera* camera);
        void FreeCameraSetLooking(Solar::Scene::FreeCamera* camera, Solar::F32 xoffset, Solar::F32 yoffset);
        void FreeCameraSetPosition(Solar::Scene::FreeCamera* camera, const Solar::U8 direction);
        void FreeCameraUpdateVectors(Solar::Scene::FreeCamera* camera);
    };
};

#endif