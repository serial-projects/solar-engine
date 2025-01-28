#include "Solar/Core/Provider/Load/DataFile.hpp"
#include "Solar/Core/Provider/Load/Mesh.hpp"
#include "Solar/Core/Provider/Load/RawMesh.hpp"

#include "Solar/Config.hpp"
#include "Solar/Validator.hpp"

Progator::Objects::Mesh* Solar::Core::Provider::Load::Mesh(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    const Solar::Types::Basic::String& object,
    const Solar::Types::Basic::String& render_unit_key
)
{
    const Solar::Types::Basic::String cache_tag = 
        "Mesh#" + site + "@" + object + "?" + render_unit_key;
    Progator::Objects::Mesh* current_mesh;
    if(warehouse->packages.find(cache_tag) != warehouse->packages.end())
    {
        Solar::Core::Provider::Package* cache_package =
            warehouse->packages.at(cache_tag);
        current_mesh =
            (Progator::Objects::Mesh*)(Solar::Core::Provider::PackageGet(cache_package));
    }
    else
    {
        Solar::Core::Graphics::Unit* rendering_unit =
            Solar::Core::Graphics::UnitsGetUnit(warehouse->units, render_unit_key);
        if(rendering_unit == nullptr)
        {
            warehouse->validator.SetError(
                Solar::ValidatorCodes::WarehouseInvalidRenderingUnit,
                "Unable to open: %s, due invalid memory unit: %s",
                site.c_str(),
                render_unit_key.c_str()
            );
            goto skip_due_invalid_rendering_unit;
        }
        
        /* NOTE: load the raw mesh: */
    }
    skip_due_invalid_rendering_unit:
    return current_mesh;
}