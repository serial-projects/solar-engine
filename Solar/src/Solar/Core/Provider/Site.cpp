#include "Solar/Core/Provider/Site.hpp"

std::optional<Solar::Core::Provider::SitePathAndKeyResult> 
Solar::Core::Provider::FromSiteGetAndSolvePathAndKey(
    Solar::Core::Provider::Warehouse *warehouse,
    const Solar::Types::Basic::String &key
)
{
    /* NOTE: solve for the path; index 0 = path / index 1 = key! */
    auto split_result = Logica::Data::String::Split(key, ':');
    if(split_result.size() != 2)    
        return std::nullopt;
    
    /* extract from the extract: */
    const Solar::Types::Basic::String path  = split_result.at(0);
    auto path_return = Solar::Core::Provider::WarehouseGetPath(warehouse, path);
    if(!path_return.has_value())
        return std::nullopt;
    
    /* done, we have everything to make the pair: */
    return std::make_pair( path_return.value(), split_result.at(1) );
}