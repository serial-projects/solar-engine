#ifndef SolarCoreProviderLoadRawMesh_hpp
#define SolarCoreProviderLoadRawMesh_hpp

#include "Solar/Core/Provider/Warehouse.hpp"
#include "Fera/Fera.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Provider
        {
            namespace Load
            {
                /// @brief Load an RAW mesh, this mesh is used to the construction of the mesh 
                /// itself and contains the buffer ready for the Progator.
                /// @param warehouse the warehouse where the packages are.
                /// @param site the site of the package.
                /// @return possibly the mesh.
                Fera::Meshing::Mesh* RawMesh(
                    Solar::Core::Provider::Warehouse* warehouse,
                    const Solar::Types::Basic::String& site
                );
            };
        };
    };
};

#endif