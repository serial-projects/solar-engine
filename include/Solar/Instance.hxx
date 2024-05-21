#ifndef solar_instance_hxx
#define solar_instance_hxx

#include "Solar/Core/Shared.hxx"
#include "Solar/Scene/Mode.hxx"

namespace Solar
{
    class Instance
    {
        public:
        Solar::Core::Shared shared_core;
        Solar::Scene::Mode scene_mode;

        void Init();
        void InitializeOpenGL();
        void InitializeVulkan();

        void Loop();
        void Tick();
        void Draw();
        
        void Quit();
    };
};

#endif
// Solar/Instance.hxx: