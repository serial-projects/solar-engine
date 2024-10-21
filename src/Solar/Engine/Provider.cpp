#include "Solar/Engine/Provider.hpp"
#include "Solar/Support/FS.hpp"

#include <iostream>

Solar::Engine::Package* Solar::Engine::PackageNew()
{
    Solar::Engine::Package* proto = new Solar::Engine::Package;
    return proto;    
}

inline static void PackageDestroyShader(Solar::Engine::Package* package)
{
    Progator::ShaderDestroy( (Progator::Shader*)package->element );
}

inline static void PackageDestroyTexture(Solar::Engine::Package* package)
{
    Progator::TextureDestroy( (Progator::Texture*)package->element );
}

inline static void PackageDestroyLoadedDotObjMesh(Solar::Engine::Package* package)
{
    Solar::Support::DotObj::InterpreterDeleteBuiltMeshTable(
        (Solar::Support::DotObj::MeshTable*)package->element
    );
}

void Solar::Engine::PackageDestroy(Solar::Engine::Package* package)
{
    /* Delete from memory the package: */
    switch(package->type)
    {
        case Solar::Engine::PackageType::Shader:   
            PackageDestroyShader(package);
            break;
        case Solar::Engine::PackageType::Texture:
            PackageDestroyTexture(package);
            break;
        case Solar::Engine::PackageType::LoadedDotObjMesh:
            PackageDestroyLoadedDotObjMesh(package);
            break;
        default:
            break;
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
    return shader;
}

Solar::Support::DotObj::MeshTable* Solar::Engine::ProviderLoadMeshFromDotObj(
    Solar::Engine::Provider* provider,
    const Solar::String name
)
{
    const Solar::String cache_key = ("DotObjMesh" + name);
    Solar::Support::DotObj::MeshTable* found_mesh;
    std::cout << "A" << "\n";
    if(provider->storage.find(cache_key) == provider->storage.end())
    {
        const Solar::String dotobj_path = (provider->properties.basepath + "Meshes/" + name + ".obj");
        std::cout
            << __PRETTY_FUNCTION__
            << ": Loading mesh = "
            << dotobj_path
            << "\n";
        
        /* set the interpreter: */
        Solar::Support::DotObj::Interpreter* interpreter =
            Solar::Support::DotObj::InterpreterLoadFromFile(dotobj_path);
        Solar::Support::DotObj::MeshTable* mesh_table = 
            Solar::Support::DotObj::InterpreterBuildMeshTable(
                interpreter,
                provider->pointers,
                provider->validator
            );
        Solar::Support::DotObj::InterpreterDestroy(interpreter);
        
        /* built the package: */
        Solar::Engine::Package* new_package = Solar::Engine::PackageNew();
        new_package->element = mesh_table;
        new_package->type = Solar::Engine::PackageType::LoadedDotObjMesh;
        provider->storage.insert({cache_key, new_package});
        
        /* set the mesh: */
        found_mesh = (Solar::Support::DotObj::MeshTable*)mesh_table;
    }
    else
    {
        std::cout
            << __PRETTY_FUNCTION__
            << ": Mesh already on cache = "
            << name
            << "\n";
        Solar::Engine::Package* cached_package = provider->storage[cache_key];
        found_mesh = (Solar::Support::DotObj::MeshTable*)cached_package->element;
    }
    return found_mesh;
}

Progator::Texture* Solar::Engine::ProviderLoadTexture(Solar::Engine::Provider* provider, const Solar::String name)
{
    const Solar::String cache_key       = ("Texture" + name);
    Progator::Texture* found_texture;
    if(provider->storage.find(cache_key) == provider->storage.end())
    {
        /* not yet on cache: */
        const Solar::String image_path = provider->properties.basepath + "Textures/" + name + ".png";
        std::cout
            << __PRETTY_FUNCTION__
            << ": Loading texture = "
            << image_path
            << "\n";
        
        Progator::Texture* new_texture = Progator::TextureNew();
        Progator::TextureInit(new_texture, provider->pointers, provider->validator);
        Progator::TextureLoadFromFile(new_texture, image_path.c_str());

        /* NOTE: everything good? */
        ProgatorHelperHandleErrorValidator(
            provider->validator,
            {
                std::cerr
                    << provider->validator->log
                    << "\n";
                std::exit(-1);
            }
        );
        

        Solar::Engine::Package* new_package = Solar::Engine::PackageNew();
        new_package->element = new_texture;
        new_package->type = Solar::Engine::PackageType::Texture;
        
        provider->storage.insert({cache_key, new_package});
        found_texture = (Progator::Texture*)new_package->element;
    }
    else
    {
        std::cout
            << __PRETTY_FUNCTION__
            << ": image already on cache = "
            << name
            << "\n";
        Solar::Engine::Package* cached_package = provider->storage[cache_key];
        found_texture = (Progator::Texture*)cached_package->element;
    }

    return found_texture;
}