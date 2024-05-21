#ifndef solar_components_cube_hxx
#define solar_components_cube_hxx

#include "Solar/Components/Model.hxx"
#include "Solar/Components/World.hxx"

namespace Solar
{
    namespace Components
    {
        class Cube : public Solar::Components::Model
        {
            public:
            void Init();
            void Destroy();
        };
    };
};

#endif
// Solar/Components/Cube.hxx: