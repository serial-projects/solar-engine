#ifndef SolarEngineProvider_hpp
#define SolarEngineProvider_hpp

#include "Solar/Types.hpp"
#include "Progator/Progator.hpp"
#include "Solar/Support/DotObj/Loader.hpp"

namespace Solar
{
    namespace Engine
    {
        /* PACKAGE: This is a simple package that holds an Progator item: */
        typedef struct Package
        {
            void *element;
            Solar::U8 type;
        } Package;

        Solar::Engine::Package* PackageNew();
        void PackageDestroy(Solar::Engine::Package* package);

        enum PackageType
        {
            Shader                      = 0,
            Texture,
            LoadedDotObjMesh,
            Font
        };

        /* ProviderProperties: Sets the path for the properties:
         * basepath:    where the project root is having the folders like: Sprites, Images, Scripts...
         * renderer:    a hint for the shader loading function.
         */
        typedef struct ProviderProperties
        {
            Solar::String basepath;
            Solar::String renderer;
        } ProviderProperties;

        /* Provider: */
        typedef std::unordered_map<Solar::String, Solar::Engine::Package*> ProviderStorage;

        typedef struct Provider
        {
            Solar::Engine::ProviderProperties properties;
            Solar::Engine::ProviderStorage storage;
            Progator::Pointers* pointers;
            Progator::Validator* validator;
        } Provider;

        Solar::Engine::Provider* ProviderNew();
        void ProviderDestroy(Solar::Engine::Provider* provider);
        void ProviderInit(Solar::Engine::Provider* provider, Solar::Engine::ProviderProperties properties, Progator::Pointers* pointers, Progator::Validator* validator);

        /* LoadShader(), LoadMeshFromDotObj(), ... */
        Progator::Shader* ProviderLoadShader(Solar::Engine::Provider* provider, const Solar::String name);
        Solar::Support::DotObj::MeshTable* ProviderLoadMeshFromDotObj(Solar::Engine::Provider* provider, const Solar::String name);

        /* NOTE: those operations on the provider can be cacheable or not: */
        Progator::Texture* ProviderLoadTexture(Solar::Engine::Provider* provider, const Solar::String name);
        Progator::Texture* ProviderLoadTextureFromSprite(Solar::Engine::Provider* provider, const Solar::String name);
    };
};

#endif