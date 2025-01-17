#include "Sojson/Node/Get.hpp"

Sojson::Node* __SojsonNodeGet(
    Sojson::Node* node,
    const Sojson::NodePath& node_path,
    const Sojson::Types::U8 depth
)
{
    Sojson::Node* current_node = nullptr;
    if(depth >= node_path.size())
        current_node = node;
    else
    {
        /* this way we can keep searchin' */
        if(node->type == Sojson::NodeTypes::Table)
        {
            Sojson::RepresentativeTypes::Table* table =
                (Sojson::RepresentativeTypes::Table*)(node->value);
            Sojson::Types::String current_key =
                node_path.at(depth);
            if(table->find(current_key) != table->end())
            {
                current_node = __SojsonNodeGet(
                    table->at(current_key),
                    node_path,
                    depth + 1
                );
            }
        }
    }
    return current_node;
}

Sojson::Node* Sojson::NodeGet(
    Sojson::Node* node,
    const Sojson::NodePath& node_path
)
{
    return __SojsonNodeGet(
        node,
        node_path,
        0
    );
}

Sojson::Node* Sojson::NodeGet(
    Sojson::Node* node,
    const Sojson::Types::String& key
)
{
    Logica::Data::String::SplitResult split =
        Logica::Data::String::Split(key, '.');
    return Sojson::NodeGet(
        node,
        split
    );
}

Sojson::Node* Sojson::NodeGet(
    Sojson::Node* node,
    const Sojson::Types::CH8* key
)
{
    return Sojson::NodeGet(node, Sojson::Types::String(key));
}