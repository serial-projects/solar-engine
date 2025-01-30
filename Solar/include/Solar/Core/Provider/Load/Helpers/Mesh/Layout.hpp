#ifndef SolarCoreProviderLoadHelpersMeshLayout_hpp
#define SolarCoreProviderLoadHelpersMeshLayout_hpp

#include "Progator/Progator.hpp"
#include "Solar/Core/Provider/Warehouse.hpp"
#include "Solar/Types.hpp"

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
                        typedef std::vector<Progator::Types::Specifics::Mesh::Layout> Layouts;

                        /// @brief this function will get from the recipe the layouts, meaning
                        /// it MIGHT crash the warehouse in case of an invalid recipe.
                        /// @param warehouse the warehouse to crash.
                        /// @param recipe the recipe of the mesh.
                        /// @return maybe the layouts.
                        std::optional<Solar::Core::Provider::Load::Helpers::Mesh::Layouts>
                        GetMeshLayouts(
                            Solar::Core::Provider::Warehouse* warehouse,
                            const Solar::Types::Basic::String& site,
                            Sojson::Node* recipe
                        );
                    };
                };
            };
        };
    };
};

#endif