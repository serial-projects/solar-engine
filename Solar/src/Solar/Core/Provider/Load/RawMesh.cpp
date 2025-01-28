#include "Solar/Core/Provider/Load/RawMesh.hpp"
#include "Solar/Core/Provider/Load/DataFile.hpp"
#include "Solar/Core/Provider/Site.hpp"

#include "Solar/Config.hpp"
#include "Solar/Validator.hpp"

#include <iostream>

/* 1-) First Stage: Load The Recipe */

static inline Sojson::Node* __SolarCoreProviderLoadRawMeshAdquireRecipe(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site
)
{
    Sojson::Node* current_recipe = 
        Solar::Core::Provider::Load::DataFile(warehouse, site);
    return current_recipe;
}

static Fera::Meshing::Mesh* __SolarCoreProviderLoadRawMeshUseOBJBackend(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    /* const Solar::Types::Basic::String& object, */
    /* Solar::Core::Graphics::Unit* rendering_unit, */
    const Solar::Types::Basic::String& file,
    Sojson::Node* recipe
)
{
    Logica::Types::Basic::String actual_file_path;
    Logica::Types::Stream::FileBuffer file_buffer;
    Fera::Meshing::Mesh* file_result_mesh = nullptr;
    Sojson::Node* recipe_obj_specific_tuning = nullptr;
    Fera::Backends::OBJ::Interpreter::Properties properties;
    Fera::Backends::OBJ::Interpreter::Instance instance;

    /* 0-) Load the actual file path: */
    auto file_path = Solar::Core::Provider::FromSiteGetAndSolvePathAndKey(
        warehouse,
        file
    );
    if(!file_path.has_value())
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseInvalidSite,
            "Unable to build mesh: %s, due invalid site: %s",
            site.c_str(),
            file.c_str()
        );
        goto skip_due_error;
    }

    /* NOTE: the .OBJ extension must be provided! */
    actual_file_path = file_path.value().first + "/" + file_path.value().second;

    /* 1-) Load the stream: */
    if(!file_buffer.SetFile(actual_file_path))
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseMeshFileNotFound,
            "Unable to build mesh: %s, due file not found: %s (or = %s)",
            site.c_str(),
            file.c_str(),
            actual_file_path.c_str()
        );
        goto skip_due_error;
    }

    /* 2-) Load the properties: */
    properties = {
        .V_size     = SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_VSIZE_DEFAULT,
        .VT_size    = SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_VTSIZE_DEFAULT,
        .VN_size    = SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_VNSIZE_DEFAULT,
        .F_size     = SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_FSIZE_DEFAULT
    };
    recipe_obj_specific_tuning = Sojson::NodeGet(recipe, "OBJ");
    if(recipe_obj_specific_tuning)
    {
        /* that case the properties are REAL ;-) */
        Sojson::Node* obj_specific_vsize_node =
            Sojson::NodeGet(recipe_obj_specific_tuning, "V_size");
        Sojson::Node* obj_specific_vtsize_node =
            Sojson::NodeGet(recipe_obj_specific_tuning, "VT_size");
        Sojson::Node* obj_specific_vnsize_node =
            Sojson::NodeGet(recipe_obj_specific_tuning, "VN_size");
        Sojson::Node* obj_specific_fsize_node =
            Sojson::NodeGet(recipe_obj_specific_tuning, "F_size");
        /* now do the maybe conversions: */
        Sojson::CastNode::Possibly::Integer maybe_obj_specific_vsize =
            Sojson::CastNode::Integer(obj_specific_vsize_node);
        Sojson::CastNode::Possibly::Integer maybe_obj_specific_vtsize =
            Sojson::CastNode::Integer(obj_specific_vtsize_node);
        Sojson::CastNode::Possibly::Integer maybe_obj_specific_vnsize =
            Sojson::CastNode::Integer(obj_specific_vnsize_node);
        Sojson::CastNode::Possibly::Integer maybe_obj_specific_fsize =
            Sojson::CastNode::Integer(obj_specific_fsize_node);
        properties.V_size =
            (Fera::Types::U8)(maybe_obj_specific_vsize.value_or(properties.V_size));
        properties.VT_size =
            (Fera::Types::U8)(maybe_obj_specific_vtsize.value_or(properties.VT_size));
        properties.VN_size =
            (Fera::Types::U8)(maybe_obj_specific_vnsize.value_or(properties.VN_size));
        properties.F_size =
            (Fera::Types::U8)(maybe_obj_specific_fsize.value_or(properties.F_size));
    }

    /* 3-) Now we can begin to interpret the file: */
    instance = Fera::Backends::OBJ::Interpreter::InstanceNew();
    Fera::Backends::OBJ::Interpreter::InstanceInit(&instance, &file_buffer);
    instance.properties = properties;

    Fera::Backends::OBJ::Interpreter::InstanceParse(&instance);

    file_result_mesh = Fera::Backends::OBJ::Interpreter::InstanceGetMesh(&instance);

    /* 4-) check for errors: */
    if(instance.validator.GetCode() != Fera::Backends::OBJ::Interpreter::InstanceErrors::Ok)
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseMeshBadOBJFile,
            "Unable to build mesh: %s, due invalid OBJ file: %s",
            site.c_str(),
            file.c_str()
        );
        goto skip_due_error;
    }

    /* 5-) finally, do the cleanup here: */
    file_buffer.Close();
    Fera::Backends::OBJ::Interpreter::InstanceDestroy(&instance);

    skip_due_error:
    return file_result_mesh;
}

static Fera::Meshing::Mesh* __SolarCoreProviderLoadRawMeshFromRecipe(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Sojson::Node* recipe
)
{
    /* This will be HUB for the Fera::Meshing::Mesh */
    
    /* Define some types (we will be working with labels): */
    Sojson::Node* recipe_type_node;
    Sojson::Node* recipe_type_file;
    Sojson::CastNode::Possibly::String maybe_recipe_type;
    Sojson::CastNode::Possibly::String maybe_recipe_file;
    Fera::Meshing::Mesh* file_result_mesh;

    /* First: Adquire the Type of the file we are working with: */
    recipe_type_node = Sojson::NodeGet(recipe, "type");
    maybe_recipe_type = Sojson::CastNode::String(recipe_type_node);
    
    if(!maybe_recipe_type.has_value())
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseInvalidMeshRecipe,
            "Unable to build mesh: %s, due lack of type on recipe!",
            site.c_str()
        );
        goto skip_due_invalid_mesh_recipe;
    }

    recipe_type_file = Sojson::NodeGet(recipe, "file");
    maybe_recipe_file = Sojson::CastNode::String(recipe_type_file);

    if(!maybe_recipe_file.has_value())
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseInvalidMeshRecipe,
            "Unable to build mesh: %s, due lack of file on recipe!",
            site.c_str()
        );
        goto skip_due_invalid_mesh_recipe;
    }

    /* Second: Now begin to redirect this to the correct backend function that will (hopefully) 
     * load the file for us.
     */

    if(maybe_recipe_type.value() == "OBJ")
    {
        file_result_mesh = __SolarCoreProviderLoadRawMeshUseOBJBackend(
            warehouse,
            site,
            maybe_recipe_file.value(),
            recipe
        );
        /* NOTE: handle OBJ errors here: */
        if(file_result_mesh == nullptr)
            goto skip_due_invalid_mesh_recipe;
    }
    else
    {
        /* invalid type (or unsupported backend): */
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseInvalidMeshRecipe,
            "Unable to build mesh: %s, due invalid mesh type: \"%s\"",
            site.c_str(),
            maybe_recipe_type.value().c_str()
        );
        goto skip_due_invalid_mesh_recipe;
    }

    skip_due_invalid_mesh_recipe:
    return file_result_mesh;
}

Fera::Meshing::Mesh* Solar::Core::Provider::Load::RawMesh(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site
)
{
    const Solar::Types::Basic::String& cache_tag =  
        "RawMesh#" + site;
    Fera::Meshing::Mesh* current_raw_mesh;
    if(warehouse->packages.find(cache_tag) != warehouse->packages.end())
    {
        Solar::Core::Provider::Package* cache_package =
            warehouse->packages.at(cache_tag);
        current_raw_mesh =
            (Fera::Meshing::Mesh*)(Solar::Core::Provider::PackageGet(cache_package));
    }
    else
    {
        /* DO the actual loading: */
        Sojson::Node* recipe = __SolarCoreProviderLoadRawMeshAdquireRecipe(warehouse, site);
        if(recipe == nullptr)
            goto skip_due_invalid_recipe;
        current_raw_mesh = __SolarCoreProviderLoadRawMeshFromRecipe(
            warehouse,
            site,
            recipe
        );
        if(current_raw_mesh == nullptr)
            goto skip_due_invalid_recipe;
        
        /* Finally, do cache the result: */
        Solar::Core::Provider::WarehouseAddCache(
            warehouse,
            cache_tag,
            Solar::Core::Provider::PackageTypes::RawMesh,
            (void*)current_raw_mesh
        );
    }
    skip_due_invalid_recipe:
    return current_raw_mesh;
}