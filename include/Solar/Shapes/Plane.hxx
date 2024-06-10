#ifndef solar_shapes_plane_hxx
#define solar_shapes_plane_hxx

#include "Solar/Core/Storage.hxx"
#include "Solar/Math/Vector3.hxx"
#include "Solar/Shapes/Mesh.hxx"

namespace Solar
{
    namespace Shapes
    {
        // This is an basic 2D plane that can be represented on 3D space:
        class Plane : public Solar::Shapes::Mesh
        {
            public:
            void Init();
            void Destroy();
        };
    };
};

#endif
// Solar/Shapes/Plane.hxx: