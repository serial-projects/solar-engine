#ifndef SolarCoreProviderLoadDatafile_hpp
#define SolarCoreProviderLoadDatafile_hpp

#include "Solar/Core/Provider/Warehouse.hpp"
#include "Sojson/Sojson.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Provider
        {
            namespace Load
            {
                Sojson::Node* Datafile(Solar::Core::Provider::Warehouse* warehouse, const Solar::Types::Basic::String& site);
            };
        };
    };
};

#endif