#include "Solar/Core/Provider/Load/Helpers/Mesh/Layout.hpp"
#include "Solar/Validator.hpp"

#include <iostream>

/// @brief Table to get the size of the types.
static std::unordered_map<Solar::Types::Basic::String, Solar::Types::Basic::U8>
__SolarCoreProviderLoadHelpersMeshGetMeshLayoutsTypeSize = 
{
    {"float",   sizeof(Progator::Types::Basic::F32)},
    {"uint",    sizeof(Progator::Types::Basic::U32)},
    {"int",     sizeof(Progator::Types::Basic::I32)}
};

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
        Sojson::Node* layout_type_node = Sojson::NodeGet(layout_node, "type");
        Sojson::Node* layout_size_node = Sojson::NodeGet(layout_node, "amount");
        auto possible_layout_type_node = Sojson::CastNode::String(layout_type_node);
        auto possible_layout_size_node = Sojson::CastNode::Integer(layout_size_node);
        if(possible_layout_size_node.has_value() && possible_layout_type_node.has_value())
        {
            if(
                __SolarCoreProviderLoadHelpersMeshGetMeshLayoutsTypeSize.find(
                    possible_layout_type_node.value()
                ) == __SolarCoreProviderLoadHelpersMeshGetMeshLayoutsTypeSize.end()
            )
            {
                /* fail, since we need to count: */
                return std::nullopt;
            }
            total_layout_size += (
                __SolarCoreProviderLoadHelpersMeshGetMeshLayoutsTypeSize.at(
                    possible_layout_type_node.value()
                )
                * possible_layout_size_node.value()
            );
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
    auto maybe_layout_size = __SolarCoreProviderLoadHelpersMeshGetMeshLayoutsGetLayoutFullsize(
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
        Sojson::Node* layout_type_node = Sojson::NodeGet(layout_node, "type");
        Sojson::Node* layout_size_node = Sojson::NodeGet(layout_node, "amount");
        auto possible_layout_type_node = Sojson::CastNode::String(layout_type_node);
        auto possible_layout_size_node = Sojson::CastNode::Integer(layout_size_node);

        layout.id           = index;
        layout.size         = maybe_layout_size.value();
        layout.stride       = 
            __SolarCoreProviderLoadHelpersMeshGetMeshLayoutsTypeSize.at(
                possible_layout_type_node.value()
            );
        layout.stride_size  = possible_layout_size_node.value();
        layout.padding      = current_padding;
        current_padding     += (layout.stride * layout.stride_size);
        building_layouts.push_back(layout);
    }
    
    return building_layouts;
}