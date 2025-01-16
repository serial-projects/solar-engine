#include "Sojson/Node/Structure.hpp"
#include "Sojson/Types.hpp"

Sojson::Node* Sojson::NodeNew()
{
    Sojson::Node* node = new Sojson::Node;
    return node;
}

/* FUNCTIONS to destroy the Node: */
void Sojson::NodeDestroy(
    Sojson::Node* node
)
{
    switch(node->type)
    {
        case Sojson::NodeTypes::Null:
            /* NOTE: for your sanity, null keywords are not allocated on memory! */
            break;
        case Sojson::NodeTypes::Integer:
            delete (Sojson::RepresentativeTypes::Integer*)(node->value);
            break;
        case Sojson::NodeTypes::Decimal:   
            delete (Sojson::RepresentativeTypes::Decimal*)(node->value);
            break;
        case Sojson::NodeTypes::String:    
            delete (Sojson::RepresentativeTypes::String*)(node->value);
            break;
        case Sojson::NodeTypes::Boolean:
            delete (Sojson::RepresentativeTypes::Boolean*)(node->value);
            break;
        case Sojson::NodeTypes::List:
            {
                Sojson::RepresentativeTypes::List* lv =
                    (Sojson::RepresentativeTypes::List*)(node->value);
                for(Sojson::Types::U32 index=0; index < lv->size(); ++index)
                    Sojson::NodeDestroy(lv->at(index));
            };
            delete (Sojson::RepresentativeTypes::List*)(node->value);
            break;
        case Sojson::NodeTypes::Table:
            {
                Sojson::RepresentativeTypes::Table* tv =
                    (Sojson::RepresentativeTypes::Table*)(node->value);
                for(auto& content : *tv)
                    Sojson::NodeDestroy(content.second);
            };
            delete (Sojson::RepresentativeTypes::Table*)(node->value);
            break;
        default:
            /* NOTE: assume there is either no data or the data was corrupted. */
            break;
    };
    delete node;
}

void Sojson::NodeInit(
    Sojson::Node* node,
    void* value,
    const Logica::Types::Basic::U8 type
)
{
    node->value = value;
    node->type = type;
}