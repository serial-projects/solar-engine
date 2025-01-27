#include "Solar/Core/Provider/Warehouse.hpp"

#include <iostream>

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

std::optional<Solar::Types::Basic::String> Solar::Core::Provider::WarehouseGetPath(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& key
)
{
    if(warehouse->paths.find(key) == warehouse->paths.end())
        return std::nullopt;
    return warehouse->paths.at(key);
}

void Solar::Core::Provider::WarehouseAddCache(
    Solar::Core::Provider::Warehouse *warehouse,
    const Solar::Types::Basic::String &key,
    const Solar::Types::Basic::U8 type,
    void *content
)
{
    if(warehouse->packages.find(key) == warehouse->packages.end())
    {
        /* NOTE: actually create the package. */
        Solar::Core::Provider::Package* package = Solar::Core::Provider::PackageNew();
        Solar::Core::Provider::PackageInit(package, content, type);
        warehouse->packages.insert({ key, package });
    }
    else
    {
        /* NOTE: if that ever happen, it means there is a bug on the cache key system that is
         * in some way dissonant with the actual key! */
        std::cout
            << __PRETTY_FUNCTION__
            << ": already cached package = "
            << key
            << ", potentially bug?\n";
        std::abort();
    }
}

void Solar::Core::Provider::WarehouseAddCacheWithRenderingUnitOwnership(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& key,
    const Solar::Types::Basic::U8 type,
    void* content,
    Solar::Core::Graphics::Unit* rendering_unit
)
{
    if(warehouse->packages.find(key) == warehouse->packages.end())
    {
        Solar::Core::Provider::Package* package = Solar::Core::Provider::PackageNew();
        Solar::Core::Provider::PackageInit(package, content, type);
        Solar::Core::Provider::PackageSetRenderingUnitOwnership(package, rendering_unit);
        warehouse->packages.insert({ key, package });
    }
    else
    {
        /* NOTE: if that ever happen, it means there is a bug on the cache key system that is
         * in some way dissonant with the actual key! */
        std::cout
            << __PRETTY_FUNCTION__
            << ": already cached package = "
            << key
            << ", potentially bug?\n";
        std::abort();
    }
}