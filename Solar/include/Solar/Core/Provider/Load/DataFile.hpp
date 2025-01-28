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
                /// @brief Loads an data file and put it on cache ;-)
                /// @param warehouse the warehouse to keep everything.
                /// @param site the site for the package.
                /// @return possibly the file.
                Sojson::Node* DataFile(Solar::Core::Provider::Warehouse* warehouse, const Solar::Types::Basic::String& site);
            };
        };
    };
};

#endif