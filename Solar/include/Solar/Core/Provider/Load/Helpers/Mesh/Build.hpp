#ifndef SolarCoreProviderLoadHelpersMeshBuild_hpp
#define SolarCoreProviderLoadHelpersMeshBuild_hpp

#include "Fera/Fera.hpp"
#include "Progator/Progator.hpp"

/* We need the layout to formalize the progator mesh: */
#include "Solar/Core/Provider/Load/Helpers/Mesh/Layout.hpp"
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
                        Progator::Objects::Mesh* Build(
                            Solar::Core::Graphics::Unit* rendering_unit,
                            Fera::Meshing::MeshUnitTypes::Object& object,
                            Solar::Core::Provider::Load::Helpers::Mesh::Layouts& layouts
                        );
                    };
                };
            };
        };
    };
};

#endif