#ifndef solar_components_plane_hxx
#define solar_components_plane_hxx

#include "Solar/Shapes/Model.hxx"
#include "Solar/Shapes/World.hxx"
#include "Solar/Core/Storage.hxx"

#include "Solar/Math/Vector3.hxx"

namespace Solar
{
    namespace Shapes
    {
        // This is an basic 2D plane that can be represented on 3D space:
        class Plane : public Solar::Shapes::Model
        {
            public:
            void Init();
            void Destroy();
        };
    };
};

#endif
// Solar/Shapes/Plane.hxx: