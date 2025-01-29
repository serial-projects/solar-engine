#ifndef SolarCoreProviderLoadHelpersMeshSurf_hpp
#define SolarCoreProviderLoadHelpersMeshSurf_hpp

#include "Fera/Fera.hpp"
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
                namespace Helpers
                {
                    namespace Mesh
                    {
                        /// @brief Surf function is the function used to get from the mesh the
                        /// object you actually want, that is due Fera having support for hierachy
                        /// and allowing for groups and etc.
                        /// @param warehouse the warehouse will be our validator since this is part
                        /// of the loading process of an Mesh, so failure will be set there.
                        /// @param mesh the mesh to be searched.
                        /// @param object the object key.
                        /// @return the object itself.
                        Fera::Meshing::MeshUnitTypes::Object Surf(
                            Solar::Core::Provider::Warehouse* warehouse,
                            Fera::Meshing::Mesh* mesh,
                            const Solar::Types::Basic::String& object
                        );
                    }
                };
            };
        };
    };
};

#endif