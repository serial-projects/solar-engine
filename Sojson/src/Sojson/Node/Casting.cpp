#include "Sojson/Node/Casting.hpp"

std::optional<Sojson::RepresentativeTypes::Integer> Sojson::CastNode::Integer(
    Sojson::Node* node
)
{
    if(node->type == Sojson::NodeTypes::Integer)
    {
        Sojson::RepresentativeTypes::Integer value;
        value = *(Sojson::RepresentativeTypes::Integer*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}

std::optional<Sojson::RepresentativeTypes::Decimal> Sojson::CastNode::Decimal(
    Sojson::Node* node
)
{
    if(node->type == Sojson::NodeTypes::Decimal)
    {
        Sojson::RepresentativeTypes::Decimal value;
        value = *(Sojson::RepresentativeTypes::Decimal*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}

std::optional<Sojson::RepresentativeTypes::String> Sojson::CastNode::String(
    Sojson::Node* node
)
{
    if(node->type == Sojson::NodeTypes::String)
    {
        Sojson::RepresentativeTypes::String value;
        value = *(Sojson::RepresentativeTypes::String*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}

std::optional<Sojson::RepresentativeTypes::Boolean> Sojson::CastNode::Boolean(
    Sojson::Node* node
)
{
    if(node->type == Sojson::NodeTypes::Boolean)
    {
        Sojson::RepresentativeTypes::Boolean value;
        value = *(Sojson::RepresentativeTypes::Boolean*)(node->value);
        return value;
    }
    else
        return std::nullopt;
}