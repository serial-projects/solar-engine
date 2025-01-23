#ifndef SolarCoreProviderWarehouse_hpp
#define SolarCoreProviderWarehouse_hpp

// NOTE: symbol order:
// : -> split the path from the key itself;
//      assume path "root" is: "/home/user/game/", an key like: root:Settings.json will result in:
//      /home/user/game/Settings.json
//      Everything that comes after the ':' is a key, no matter if there is another splits.
// @ -> split reserved for certain objects;

// NOTE: for naming objects on the cache is:
//  + Data Files (Sojson):          PATH: KEY
//  + Mesh Files (Fera):            PATH: KEY $ MESH NAME
//  + Shader (Progator):            PATH: KEY $ (provide the renderer base as argument)

#include "Solar/Types.hpp"
#include "Solar/Core/Graphics.hpp"
#include "Solar/Core/Provider/Package.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Provider
        {
            /// @brief An object that contains all the cache.
            typedef std::unordered_map<
                Solar::Types::Basic::String,
                Solar::Core::Provider::Package*
            > PackageTable;

            /// @brief An object that contains all the keys to the path.
            typedef std::unordered_map<
                Solar::Types::Basic::String,
                Solar::Types::Basic::String
            > PathTable;

            /// @brief Name is self explanatory, but this contains all the current loaded packages
            /// that the engine needs, everything from datafiles, meshes, textures and etc. BUT!
            /// There is a important policy here, each texture is on it's own renderer, this makes
            /// everything more complicated. Consider the following, an texture should be attached
            /// to its RENDERER or it WON'T work or it will be a memory violation. So, to avoid
            /// repetition, see the stand for naming cache.
            struct Warehouse
            {
                Solar::Core::Provider::PackageTable packages;
                Solar::Core::Provider::PathTable paths;
                Solar::Core::Graphics::Units* units;
                Logica::Control::Validator validator;
            };

            Solar::Core::Provider::Warehouse WarehouseNew();
            void WarehouseDestroy(Solar::Core::Provider::Warehouse* warehouse);
            void WarehouseInit(Solar::Core::Provider::Warehouse* warehouse, Solar::Core::Graphics::Units* units);
            void WarehouseAddPath(Solar::Core::Provider::Warehouse* warehouse, const Solar::Types::Basic::String& key, const Solar::Types::Basic::String& path);
        };
    };
};

#endif