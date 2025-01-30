#include "Solar/Core/Provider/Load/Helpers/Mesh/Layout.hpp"
#include "Solar/Validator.hpp"

#include <iostream>

static std::optional<Solar::Types::Basic::U8>
__SolarCoreProviderLoadHelpersMeshGetMeshLayoutsGetLayoutFullsize(
    Sojson::RepresentativeTypes::List* layout
)
{
    Solar::Types::Basic::U8 total_layout_size = 0;
    for(Solar::Types::Basic::U8 index=0; index < layout->size() && index < UINT8_MAX; ++index)
    {
        /* NOTE: we don't actually need the name, we just need: type and amount fields. */
        Sojson::Node* layout_node = layout->at(index);
        Sojson::Node* layout_size_node = Sojson::NodeGet(layout_node, "size");
        auto possible_layout_size_node = Sojson::CastNode::Integer(layout_size_node);
        if(possible_layout_size_node.has_value())
        {
            total_layout_size += possible_layout_size_node.value();
        }
        else
            /* fail, since we need to count: */
            return std::nullopt;
    }
    return total_layout_size;
}

std::optional<Solar::Core::Provider::Load::Helpers::Mesh::Layouts>
Solar::Core::Provider::Load::Helpers::Mesh::GetMeshLayouts(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& site,
    Sojson::Node* recipe
)
{
    Solar::Core::Provider::Load::Helpers::Mesh::Layouts building_layouts;
    
    /* Here we want an list: */
    Sojson::Node* layout_node = Sojson::NodeGet(recipe, "layouts");
    auto possible_layout_node = Sojson::CastNode::List(layout_node);
    if(!possible_layout_node)
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseInvalidMeshRecipe,
            "unable to load layouts (no field) from mesh recipe: %s",
            site.c_str()
        );
        return std::nullopt;
    }

    /* get the entire size of the mesh: */
    auto maybe_layout_size = 
        __SolarCoreProviderLoadHelpersMeshGetMeshLayoutsGetLayoutFullsize(
            possible_layout_node.value()
        );
    
    if(!maybe_layout_size)
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseInvalidMeshRecipe,
            "unable to load layouts (invalid field) from mesh recipe: %s",
            site.c_str()
        );
        return std::nullopt;
    }

    /* begin the layout construction: 
     * 
     * NOTE: we do a few assumptions here:
     * 1-) everything is valid, that is: type and amount (we have checked on the counting);
     */
    Solar::Types::Basic::U8 current_padding = 0;
    for(
        Solar::Types::Basic::U8 index=0;
        index < possible_layout_node.value()->size() && index < UINT8_MAX;
        ++index
    )
    {
        Progator::Types::Specifics::Mesh::Layout layout;
        Sojson::Node* layout_node = possible_layout_node.value()->at(index);
        Sojson::Node* layout_size_node = Sojson::NodeGet(layout_node, "size");
        auto possible_layout_size_node = Sojson::CastNode::Integer(layout_size_node);
        
        std::cout
            << __PRETTY_FUNCTION__
            << ": "
            << (int)possible_layout_size_node.value()
            << " | "
            << (int)maybe_layout_size.value()
            << "\n";

        layout.id           = index;
        layout.size         = possible_layout_size_node.value();
        layout.stride       = maybe_layout_size.value();
        layout.padding      = current_padding;
        building_layouts.push_back(layout);

        /* push the current padding: */
        current_padding     += possible_layout_size_node.value();
    }
    
    return building_layouts;
}