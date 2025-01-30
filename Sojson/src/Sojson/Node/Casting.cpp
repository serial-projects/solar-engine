#include "Sojson/Node/Casting.hpp"

Sojson::CastNode::Possibly::Integer Sojson::CastNode::Integer(
    Sojson::Node* node
)
{
    /* NOTE: using NodeGet() might return null sometimes, so ignore null and mark as impossible to
     * cast values.
     */
    if(node == nullptr)
        return std::nullopt;
    
    /* if the node isn't null: */
    if(node->type == Sojson::NodeTypes::Integer)
    {
        Sojson::RepresentativeTypes::Integer value;
        value = *(Sojson::RepresentativeTypes::Integer*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}

Sojson::CastNode::Possibly::Decimal Sojson::CastNode::Decimal(
    Sojson::Node* node
)
{
    if(node == nullptr)
        return std::nullopt;

    if(node->type == Sojson::NodeTypes::Decimal)
    {
        Sojson::RepresentativeTypes::Decimal value;
        value = *(Sojson::RepresentativeTypes::Decimal*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}

Sojson::CastNode::Possibly::String Sojson::CastNode::String(
    Sojson::Node* node
)
{
    if(node == nullptr)
        return std::nullopt;

    if(node->type == Sojson::NodeTypes::String)
    {
        Sojson::RepresentativeTypes::String value;
        value = *(Sojson::RepresentativeTypes::String*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}

Sojson::CastNode::Possibly::Boolean Sojson::CastNode::Boolean(
    Sojson::Node* node
)
{
    if(node == nullptr)
        return std::nullopt;

    if(node->type == Sojson::NodeTypes::Boolean)
    {
        Sojson::RepresentativeTypes::Boolean value;
        value = *(Sojson::RepresentativeTypes::Boolean*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}

Sojson::CastNode::Possibly::List Sojson::CastNode::List(
    Sojson::Node* node
)
{
    if(node == nullptr)
        return std::nullopt;

    if(node->type == Sojson::NodeTypes::List)
    {
        Sojson::RepresentativeTypes::List value;
        value = *(Sojson::RepresentativeTypes::List*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}