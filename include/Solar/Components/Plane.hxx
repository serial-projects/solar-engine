#ifndef solar_components_plane_hxx
#define solar_components_plane_hxx

#include "Solar/Components/Model.hxx"
#include "Solar/Components/World.hxx"
#include "Solar/Core/Storage.hxx"

#include "Solar/Math/Vector3.hxx"

namespace Solar
{
    namespace Components
    {
        // This is an basic 2D plane that can be represented on 3D space:
        class Plane : public Solar::Components::Model
        {
            public:
            void Init();
            void Destroy();
        };
    };
};

#endif
// Solar/Components/Plane.hxx: