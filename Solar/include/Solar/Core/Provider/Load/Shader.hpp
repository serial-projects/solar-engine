#ifndef SolarCoreProviderLoadShader_hpp
#define SolarCoreProviderLoadShader_hpp

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
                /// @brief Loads an shader from the cache if possible.
                /// @param warehouse the warehouse to search the cache.
                /// @param site the site of the package.
                /// @param render_unit the render the shader should be loaded or was loaded.
                /// @return the shader.
                Progator::Objects::Shader* Shader(
                    Solar::Core::Provider::Warehouse* warehouse,
                    const Solar::Types::Basic::String& site,
                    const Solar::Types::Basic::String& render_unit_key
                );
            };
        };
    };
};

#endif