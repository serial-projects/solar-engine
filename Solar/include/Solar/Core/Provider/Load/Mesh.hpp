#ifndef SolarCoreProviderLoadMesh_hpp
#define SolarCoreProviderLoadMesh_hpp

#include "Fera/Fera.hpp"

#include "Progator/Progator.hpp"

#include "Solar/Types.hpp"
#include "Solar/Core/Provider/Warehouse.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Provider
        {
            namespace Load
            {
                /// @brief Load an mesh.
                /// @param warehouse the warehouse where the packages are.
                /// @param site the site of the package.
                /// @param object the mesh object.
                /// @param render_unit_key the render unit key.
                /// @return possibly the mesh.
                Progator::Objects::Mesh* Mesh(
                    Solar::Core::Provider::Warehouse* warehouse,
                    const Solar::Types::Basic::String& site,
                    const Solar::Types::Basic::String& object,
                    const Solar::Types::Basic::String& render_unit_key
                );
            };
        };
    };
};

#endif