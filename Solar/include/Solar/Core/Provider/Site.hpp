#ifndef SolarCoreProviderSite_hpp
#define SolarCoreProviderSite_hpp 

#include "Solar/Core/Provider/Warehouse.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Provider
        {
            /// @brief the return of GetSizeAndKey that contains on left = site and left = key.
            typedef std::pair<Solar::Types::Basic::String, Solar::Types::Basic::String>
                SitePathAndKeyResult;
            
            /// @brief maybe return the site (in case there is a ':', case not then error), this
            /// will automatically try to get the path and set on the first pair.
            /// @param key the site to be parsed.
            /// @return maybe the path (solved)/key
            std::optional<Solar::Core::Provider::SitePathAndKeyResult> FromSiteGetAndSolvePathAndKey(Solar::Core::Provider::Warehouse* warehouse, const Solar::Types::Basic::String& key);
        };
    };
};

#endif