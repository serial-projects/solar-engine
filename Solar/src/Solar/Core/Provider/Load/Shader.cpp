#include "Solar/Core/Provider/Load/Shader.hpp"
#include "Solar/Core/Provider/Load/DataFile.hpp"
#include "Solar/Core/Provider/Site.hpp"
#include "Solar/Validator.hpp"

#include <iostream>

/* NOTE: what we are loading on the shader is actually an .jsonc file, but we will decode this file
 * and load the shader from that. That makes it more flexible for OpenGL/Vulkan/etc. to operate. 
 * This datafile is called "Recipe" and it will "cook" the shader for us.
 */

static Sojson::Node* __SolarCoreProviderLoadShaderAdquireRecipe(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site
)
{
    Sojson::Node* current_node =
        Solar::Core::Provider::Load::DataFile(warehouse, site);
    return current_node;
}

/*
 * NOTE: most of the functions here are inline functions to do all the check up for the possibility
 * of an bad file/file not existing/etc. All cases must be included.
 */

#define OPTION_VERTEX       0
#define OPTION_FRAGMENT     1
#define OPTION_GEOMETRY     2

inline static void __SolarCoreProviderLoadShaderHandleErrorAndRedirectToWarehouse(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Solar::Core::Graphics::Unit* rendering_unit,
    Progator::Objects::Shader* working_shader,
    const Solar::Types::Basic::String& path
)
{
    if(rendering_unit->validator.GetCode() != Progator::ValidatorCodes::Ok)
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseFailedCompileShader,
            "Failed to compile shader %s (required from: %s), Progator says: %s",
            path.c_str(),
            site.c_str(),
            rendering_unit->validator.GetBuffer().c_str()
        );
    }
}

inline static void __SolarCoreProviderLoadShaderFromPath(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Solar::Core::Graphics::Unit* rendering_unit,
    Progator::Objects::Shader* working_shader,
    const Solar::Types::Basic::U8 option,
    const Solar::Types::Basic::String& path
)
{
    /* TODO: on the future when using disk files, do not use this function! */
    if(Logica::Data::File::Exists(path))
    {
        Logica::Types::Basic::String buffer = Logica::Data::File::Cat(path);
        switch(option)
        {
            case OPTION_VERTEX:
                Progator::Objects::ShaderSetVertexCode(
                    working_shader,
                    rendering_unit->renderer,
                    buffer.c_str()
                );
                break;
            case OPTION_FRAGMENT:
                Progator::Objects::ShaderSetFragmentCode(
                    working_shader,
                    rendering_unit->renderer,
                    buffer.c_str()
                );
                break;
            case OPTION_GEOMETRY:
                Progator::Objects::ShaderSetGeometryCode(
                    working_shader,
                    rendering_unit->renderer,
                    buffer.c_str()
                );
                break;
            default:
                /* impossible to reach code, maybe BUG? */
                std::abort();
                break;
        };
        
        /* handle errors for all the options: */
        __SolarCoreProviderLoadShaderHandleErrorAndRedirectToWarehouse(
            warehouse,
            site,
            rendering_unit,
            working_shader,
            path
        );
    }
}

inline static void __SolarCoreProviderLoadShaderFromPossibleString(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Solar::Core::Graphics::Unit* rendering_unit,
    Progator::Objects::Shader* working_shader,
    const Solar::Types::Basic::U8 option,
    Sojson::CastNode::Possibly::String& input
)
{
    /* get the value & only allows when validator is good ;-) */
    if(input.has_value() && warehouse->validator.GetCode() == Solar::ValidatorCodes::Ok)
    {
        /* find the path ? */
        auto possible_path_and_key =
            Solar::Core::Provider::FromSiteGetAndSolvePathAndKey(warehouse, input.value());
        if(possible_path_and_key.has_value())
        {
            /* NOTE: it is expected for the user to provide the extension! */
            auto path_and_key = possible_path_and_key.value();
            const Solar::Types::Basic::String path =
                path_and_key.first + path_and_key.second;
            __SolarCoreProviderLoadShaderFromPath(
                warehouse,
                site,
                rendering_unit,
                working_shader,
                option,
                path
            );
        }
    }
}

static Progator::Objects::Shader* __SolarCoreProviderLoadShaderOpenGLBackend(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Solar::Core::Graphics::Unit* rendering_unit,
    Sojson::Node* recipe
)
{
    /* Check if the recipe has backends: */
    Progator::Objects::Shader* loading_shader = nullptr;
    Sojson::Node* vertex    = Sojson::NodeGet(recipe, "vertex");
    Sojson::Node* fragment  = Sojson::NodeGet(recipe, "fragment");
    Sojson::Node* geometry  = Sojson::NodeGet(recipe, "geometry");
    auto possible_vertex    = Sojson::CastNode::String(vertex);
    auto possible_fragment  = Sojson::CastNode::String(fragment);
    auto possible_geometry  = Sojson::CastNode::String(geometry);

    /* Process the shader: */
    loading_shader = Progator::Objects::ShaderNew();
    Progator::Objects::ShaderInit(
        loading_shader,
        &rendering_unit->pointers,
        rendering_unit->renderer,
        &rendering_unit->validator
    );

    /* Load Vertex, Fragment and (maybe) Geometry Shaders: */
    __SolarCoreProviderLoadShaderFromPossibleString(
        warehouse,
        site,
        rendering_unit,
        loading_shader,
        OPTION_VERTEX,
        possible_vertex
    );

    __SolarCoreProviderLoadShaderFromPossibleString(
        warehouse,
        site,
        rendering_unit,
        loading_shader,
        OPTION_FRAGMENT,
        possible_fragment
    );

    __SolarCoreProviderLoadShaderFromPossibleString(
        warehouse,
        site,
        rendering_unit,
        loading_shader,
        OPTION_GEOMETRY,
        possible_geometry
    );

    Progator::Objects::ShaderLink(loading_shader, rendering_unit->renderer);
    Progator::Objects::ShaderCompile(loading_shader, rendering_unit->renderer);
    __SolarCoreProviderLoadShaderHandleErrorAndRedirectToWarehouse(
        warehouse,
        site,
        rendering_unit,
        loading_shader,
        /* LINKAGE: the error happened during the linking stage: */
        "<<LINKAGE/NF>>>"
    );

    return loading_shader;
}

static Progator::Objects::Shader* __SolarCoreProviderLoadShaderFromRecipe(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Solar::Core::Graphics::Unit* rendering_unit,
    Sojson::Node* recipe
)
{
    /* We will be using labels to deal with errors: */
    Sojson::Node* backend_section = nullptr;
    Progator::Objects::Shader* possibly_loaded_shader = nullptr;

    /* check if the recipe has section named "backends" */
    backend_section = Sojson::NodeGet(recipe, "backends");
    if(backend_section == nullptr)
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseMalformedShaderFile,
            "Invalid shader specification file: %s, lacking backends section!",
            site.c_str()
        );
        goto skip_due_lack_backend_section;
    }

    /* adquire the current unit rendering mode and branch from here to the desired backend shader
     * specified on the file.
     */
    switch(rendering_unit->pointers.mode)
    {
        case Progator::Base::PointersBackend::OpenGL:
            {
                /* TODO: refactor this ;-) */

                /* NOTE: get the opengl field inside backends and load the shader:*/
                Sojson::Node* opengl_field = Sojson::NodeGet(backend_section, "opengl");
                if(opengl_field == nullptr)
                {
                    warehouse->validator.SetError(
                        Solar::ValidatorCodes::WarehouseMalformedShaderFile,
                        "on shader: %s, missing on backends filed, \"opengl\" key!",
                        site.c_str()
                    );
                }
                else
                {
                    possibly_loaded_shader = __SolarCoreProviderLoadShaderOpenGLBackend(
                        warehouse,
                        site,
                        rendering_unit,
                        opengl_field
                    );
                }
            }
            break;
        default:
        /* XXX: in case on an invalid pointer/backend, then crash the whole thing, it means
         * an garbage value is here, why? the SetPointerXXX() function always set the value,
         * meaning that if there is no value here then it is potentially an BUG or memory
         * corruption.
         */
        {
            std::abort();
        }
        break;
    }

    skip_due_lack_backend_section:
    skip_due_invalid_rendering_unit:
    return possibly_loaded_shader;
}

inline static Progator::Objects::Shader* __SolarCoreProviderLoadShader(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Solar::Core::Graphics::Unit* rendering_unit
)
{
    /* 1-) get the shader recipe: */
    Sojson::Node* recipe = __SolarCoreProviderLoadShaderAdquireRecipe(warehouse, site);
    Progator::Objects::Shader* loading_shader = nullptr;
    if(recipe != nullptr)
    {
        /* 2-) load the shader itself: */
        loading_shader = __SolarCoreProviderLoadShaderFromRecipe(
            warehouse,
            site,
            rendering_unit,
            recipe
        );
    }
    return loading_shader;
}

Progator::Objects::Shader* Solar::Core::Provider::Load::Shader(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    const Solar::Types::Basic::String& render_unit_key
)
{
    const Solar::Types::Basic::String cache_tag = 
        "Shader#" + site + "?" + render_unit_key;
    Progator::Objects::Shader* current_shader = nullptr;
    if(warehouse->packages.find(cache_tag) != warehouse->packages.end())
    {
        Solar::Core::Provider::Package* cache_package =
            warehouse->packages.at(cache_tag);
        current_shader =
            (Progator::Objects::Shader*)(Solar::Core::Provider::PackageGet(cache_package));
    }
    else
    {
        /* 1-) get the rendering unit: */
        Solar::Core::Graphics::Unit* rendering_unit
            = Solar::Core::Graphics::UnitsGetUnit(warehouse->units, render_unit_key);
        if(rendering_unit == nullptr)
        {
            warehouse->validator.SetError(
                Solar::ValidatorCodes::WarehouseInvalidRenderingUnit,
                "Unable to open: %s, due invalid memory unit: %s",
                site.c_str(),
                render_unit_key.c_str()
            );
            goto skip_due_invalid_rendering_unit;
        }
        
        /* 2-) load the actual shader: */

        current_shader = __SolarCoreProviderLoadShader(
            warehouse,
            site,
            rendering_unit
        );
        if(current_shader == nullptr)
            goto skip_due_error_loading_shader;

        Solar::Core::Provider::WarehouseAddCacheWithRenderingUnitOwnership(
            warehouse,
            cache_tag,
            Solar::Core::Provider::PackageTypes::Shader,
            (void*)current_shader,
            rendering_unit
        );
    }

    skip_due_invalid_rendering_unit:
    skip_due_error_loading_shader:
    return current_shader;
}