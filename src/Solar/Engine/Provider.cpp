#include "Solar/Engine/Provider.hpp"
#include "Solar/Support/FS.hpp"

#include <iostream>

Solar::Engine::Package* Solar::Engine::PackageNew()
{
    Solar::Engine::Package* proto = new Solar::Engine::Package;
    return proto;    
}

inline void PackageDestroyShader(Solar::Engine::Package* package)
{
    Progator::ShaderDestroy( (Progator::Shader*)package->element );
}

void Solar::Engine::PackageDestroy(Solar::Engine::Package* package)
{
    /* Delete from memory the package: */
    switch(package->type)
    {
        case Solar::Engine::PackageType::Shader:    PackageDestroyShader(package); break;
        default:                                    break;
    };

    /* Remove from memory: */
    delete package;
}

Solar::Engine::Provider* Solar::Engine::ProviderNew()
{
    Solar::Engine::Provider* proto = new Solar::Engine::Provider;
    return proto;
}

void Solar::Engine::ProviderDestroy(Solar::Engine::Provider* provider)
{
    /* iterate & delete the list: */
    for(auto &content : provider->storage)
        Solar::Engine::PackageDestroy(content.second);
    delete provider;
}

void Solar::Engine::ProviderInit(Solar::Engine::Provider* provider, Solar::Engine::ProviderProperties properties, Progator::Pointers* pointers, Progator::Validator* validator)
{
    provider->properties = properties;
    provider->pointers = pointers;
    provider->validator = validator;
}

Progator::Shader* Solar::Engine::ProviderLoadShader(Solar::Engine::Provider* provider, const Solar::String name)
{
    const Solar::String cached_key = ("Shader" + name);
    Progator::Shader *shader;

    if(provider->storage.find(cached_key) == provider->storage.end())
    {
        const Solar::String calculated_path = ( provider->properties.basepath + "Shaders/" + provider->properties.renderer + "/" + name );
        const Solar::String calculated_vert_shader_path = (calculated_path + ".vert");
        const Solar::String calculated_frag_shader_path = (calculated_path + ".frag");

        /* TODO: remove or add debug exception here: */
        std::cout 
            << __PRETTY_FUNCTION__
            << ": Loading shader (Vertex: \""
            << calculated_vert_shader_path
            << "\", Fragment: \"" 
            << calculated_frag_shader_path
            << "\")\n";

        // NOTE: this isn't actually necessary, the Progator::ShaderLoadVertexCodeFromFile already
        // checks if the file exists before trying to load so... Keep going without this code.

        /* TODO: make an logging system for when the validator reports an error: */
        /* NOTE: perform the shader loading option: */
        
        shader = Progator::ShaderNew();
        Progator::ShaderInit(shader, provider->pointers, provider->validator);

        Progator::ShaderLoadVertexCodeFromFile(shader, calculated_vert_shader_path.c_str());
        ProgatorHelperHandleErrorValidator(
            provider->validator,
            {
                std::cerr << provider->validator->log << "\n";
                std::exit(-1);
            }
        );

        Progator::ShaderLoadFragmentCodeFromFile(shader, calculated_frag_shader_path.c_str());
        ProgatorHelperHandleErrorValidator(
            provider->validator,
            {
                std::cerr << provider->validator->log << "\n";
                std::exit(-1);
            }
        );

        Progator::ShaderCompile(shader);
        ProgatorHelperHandleErrorValidator(
            provider->validator,
            {
                std::cerr << provider->validator->log << "\n";
                std::exit(-1);
            }
        );

        Solar::Engine::Package* package = Solar::Engine::PackageNew();
        package->element    = shader;
        package->type       = Solar::Engine::PackageType::Shader;

        /* set to cache: */
        provider->storage.insert({cached_key, package});
    }
    else
    {
        std::cout
            << __PRETTY_FUNCTION__
            << ": Shader \""
            << name
            << "\", already on cache.\n";
        Solar::Engine::Package* package = provider->storage[cached_key];
        shader = (Progator::Shader*)package->element;
    }
    
    failed_compile_shaders:
    return shader;
}