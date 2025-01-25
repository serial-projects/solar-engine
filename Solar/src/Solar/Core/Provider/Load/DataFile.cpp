#include "Solar/Core/Provider/Load/DataFile.hpp"
#include "Solar/Core/Provider/Site.hpp"
#include "Solar/Validator.hpp"

#include <iostream>

static Sojson::Node* __SolarCoreProviderLoadDataFileFromFile(
    Solar::Core::Provider::Warehouse* warehouse,
    Logica::Types::Stream::FileBuffer* file_buffer
)
{
    Sojson::Decode::Instance instance = Sojson::Decode::InstanceNew();
    Sojson::Decode::InstanceInit(&instance, file_buffer);
    Sojson::Node* decoded_tree = Sojson::Decode::InstanceParse(&instance);
    
    /* handle errors: */
    if(instance.validator.GetCode() != Sojson::Decode::InstanceErrors::Ok)
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseLoadDataFileSojsonSyntaxError,
            "bad syntax: %s",
            instance.validator.GetBuffer().c_str()
        );
    }
    else
        Sojson::Decode::InstanceDestroy(&instance);
    return decoded_tree;
}


static Sojson::Node* __SolarCoreProviderLoadDataFile(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Core::Provider::SitePathAndKeyResult& path_and_key
)
{
    Sojson::Node* parsed_file = nullptr;

    /* Solve for the file to be loaded:
     * First = the site pattern is = root:/SomeFolder/File (we just lack the extension)
     * since the root is already solved, we just need to set the file extension, and for data
     * files it is .jsonc (json with comments, that is compatible with Sojson).
     */

    const Solar::Types::Basic::String file_path =
        path_and_key.first + path_and_key.second + ".jsonc";
    
    std::cout
        << __PRETTY_FUNCTION__
        << ": "
        << file_path
        << "\n";

    /* begin to load the file, here we require to open a buffer: */
    Logica::Types::Stream::FileBuffer file_buffer;
    if(file_buffer.SetFile(file_path))
    {
        /* NOTE: then do the right thing: */
        parsed_file = __SolarCoreProviderLoadDataFileFromFile(warehouse, &file_buffer);
        file_buffer.Close();
    }
    else
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseLoadDataFileNoFile,
            "unable to open data file: %s",
            file_path.c_str()
        );
    }

    return parsed_file;
}

Sojson::Node* Solar::Core::Provider::Load::DataFile(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site
)
{
    /* search on cache, site = <path> : <file> */
    const Solar::Types::Basic::String cache_tag = "Datafile#" + site;
    Sojson::Node* current_node = nullptr;
    if(warehouse->packages.find(cache_tag) != warehouse->packages.end())
    {
        Solar::Core::Provider::Package* cache_package = 
            warehouse->packages.at(cache_tag);
        current_node = (Sojson::Node*)Solar::Core::Provider::PackageGet(cache_package);
    }
    else
    {
        /* DO actual loading: */
        auto content = Solar::Core::Provider::FromSiteGetAndSolvePathAndKey(warehouse, site);
        if(!content.has_value())
        {
            warehouse->validator.SetError(
                Solar::ValidatorCodes::WarehouseInvalidSite,
                "invalid site: %s",
                site.c_str()
            );
            goto skip_point_due_error;
        }
        
        /* keep going: */
        current_node = __SolarCoreProviderLoadDataFile(warehouse, content.value());
        if(current_node == nullptr)
            goto skip_point_due_error;
        
        /* if not error, then cache the package on the system: */
        Solar::Core::Provider::WarehouseAddCache(
            warehouse,
            cache_tag,
            Solar::Core::Provider::PackageTypes::Datafile,
            (void*)current_node
        );
    }
    skip_point_due_error:
    return current_node;
}