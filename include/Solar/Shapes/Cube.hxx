#ifndef solar_shapes_cube_hxx
#define solar_shapes_cube_hxx

#include "Solar/Shapes/Mesh.hxx"
#include "Solar/Core/Storage.hxx"

namespace Solar
{
    namespace Shapes
    {
        class Cube : public Solar::Shapes::Mesh
        {
            public:
            void Init();
            void Destroy();
        };
    };
};

#endif
// Solar/Shapes/Cube.hxx: