#ifndef SolarCoreProviderPackage_hpp
#define SolarCoreProviderPackage_hpp

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Provider
        {
            namespace PackageTypes
            {
                enum PackageTypes
                {
                    /// @brief when nothing was set as the type.
                    No = 0,

                    /* Structural objects: */
                    
                    /// @brief datafile is usually Sojson files.
                    Datafile,

                    /// @brief raw mesh are the fera meshing.
                    RawMesh,

                    /* Rendering Objects: */

                    /// @brief texture holds an image.
                    Texture,

                    /// @brief the progator shader.
                    Shader,

                    /// @brief something that was an raw mesh and got loaded into progator.
                    Mesh,

                    /// @brief unknown errors.
                    Unknown = UINT8_MAX
                };
            };

            /// @brief An package contains the content, type and last use.
            struct Package
            {
                void*                       content;
                
                /* NOTE: on the future, merge this! 
                 * Sugestion: 0, 0, 0, 0 = type + ... = last use, so u60 for the last use.
                 */
                Solar::Types::Basic::U8     type;
                Solar::Types::Basic::U64    lastuse;
            };

            /// @brief Creates an new package to be set on the warehouse.
            /// @return the package on the heap.
            Solar::Core::Provider::Package* PackageNew();

            /// @brief Destroys the package (free from memory);
            /// @param package the package to be destroyed.
            void PackageDestroy(Solar::Core::Provider::Package* package);

            /// @brief Initialize the package.
            /// @param package the package to be initialized.
            /// @param content the pointer to your content (void*).
            /// @param type the type of the package.
            void PackageInit(Solar::Core::Provider::Package* package, void* content, const Solar::Types::Basic::U8 type);
            
            /// @brief This function will get the pointer for you AND set the lastuse to now.
            /// @param package the package to get.
            /// @return the pointer of the package.
            void* PackageGet(Solar::Core::Provider::Package* package);
        };
    };
};

#endif