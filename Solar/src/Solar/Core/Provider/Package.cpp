#include "Solar/Core/Provider/Package.hpp"

#include "Fera/Fera.hpp"
#include "Sojson/Sojson.hpp"
#include "Progator/Progator.hpp"

#include <iostream>

Solar::Core::Provider::Package* Solar::Core::Provider::PackageNew()
{
    Solar::Core::Provider::Package* package = new Solar::Core::Provider::Package;
    return package;
}

void Solar::Core::Provider::PackageDestroy(
    Solar::Core::Provider::Package* package
)
{
    /* NOTE: remove automatically this for us: */
    switch(package->type)
    {
        case Solar::Core::Provider::PackageTypes::No:
            /* NOTE: is this an useless block? */
            std::cout
                << __PRETTY_FUNCTION__
                << ": BUG? empty package found? (use GDB for debugging)\n";
            std::abort();
            break;
        /* Structural Objects: */
        case Solar::Core::Provider::PackageTypes::Datafile:
            {
                Sojson::NodeDestroy(
                    (Sojson::Node*)(package->content)
                );
            };
            break;
        case Solar::Core::Provider::PackageTypes::RawMesh:
            {
                Fera::Meshing::MeshDestroy(
                    (Fera::Meshing::Mesh*)(package->content)
                );
            };
            break;
        /* Rendering Objects: */
        case Solar::Core::Provider::PackageTypes::Texture:
            {

            };
            break;
        case Solar::Core::Provider::PackageTypes::Shader:
            {

            };
            break;
        case Solar::Core::Provider::PackageTypes::Mesh:
            {

            };
            break;
        /* probably bug ? */
        case Solar::Core::Provider::PackageTypes::Unknown:
        default:
            /* XXX: the code should never reach here! */
            std::abort();
            break;
    };
    delete package;
}

void Solar::Core::Provider::PackageInit(
    Solar::Core::Provider::Package* package,
    void* content,
    const Solar::Types::Basic::U8 type
)
{
    package->lastuse    = SDL_GetTicks64();
    package->content    = content;
    package->type       = type;
}