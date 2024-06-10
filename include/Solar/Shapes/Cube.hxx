#ifndef solar_shapes_cube_hxx
#define solar_shapes_cube_hxx

#include "Solar/Shapes/Model.hxx"
#include "Solar/Shapes/World.hxx"

namespace Solar
{
    namespace Shapes
    {
        class Cube : public Solar::Shapes::Model
        {
            public:
            void Init();
            void Destroy();
        };
    };
};

#endif
// Solar/Shapes/Cube.hxx: