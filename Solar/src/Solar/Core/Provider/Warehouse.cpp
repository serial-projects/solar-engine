#include "Solar/Core/Provider/Warehouse.hpp"

Solar::Core::Provider::Warehouse Solar::Core::Provider::WarehouseNew()
{
    Solar::Core::Provider::Warehouse warehouse;
    return warehouse;
}

void Solar::Core::Provider::WarehouseDestroy(
    Solar::Core::Provider::Warehouse* warehouse
)
{
    for(auto& content : warehouse->packages)
        Solar::Core::Provider::PackageDestroy(content.second);
}

void Solar::Core::Provider::WarehouseInit(
    Solar::Core::Provider::Warehouse* warehouse,
    Solar::Core::Graphics::Units* units
)
{
    warehouse->packages = Solar::Core::Provider::PackageTable();
    warehouse->paths = Solar::Core::Provider::PathTable();
    warehouse->validator = Logica::Control::Validator();
    warehouse->units = units;
}

void Solar::Core::Provider::WarehouseAddPath(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& key,
    const Solar::Types::Basic::String& path
)
{
    warehouse->paths.insert({key, path});
}