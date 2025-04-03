#include "Sojson/Types/Node.hpp"

std::optional<Sojson::Node::Integer> Sojson::Node::CastInteger()
{
    if(this->value == NULL || this->type != INTEGER)
        return std::nullopt;
    return *static_cast<Sojson::Node::Integer*>(this->value);
}

std::optional<Sojson::Node::Decimal> Sojson::Node::CastDecimal()
{
    if(this->value == NULL || this->type != DECIMAL)
        return std::nullopt;
    return *static_cast<Sojson::Node::Decimal*>(this->value);
}

std::optional<Sojson::Node::String> Sojson::Node::CastString()
{
    if(this->value == NULL || this->type != STRING)
        return std::nullopt;
    return *static_cast<Sojson::Node::String*>(this->value);
}

std::optional<Sojson::Node::Boolean> Sojson::Node::CastBoolean()
{
    if(this->value == NULL || this->type != BOOLEAN)
        return std::nullopt;
    return *static_cast<Sojson::Node::Boolean*>(this->value);
}

std::optional<Sojson::Node::List> Sojson::Node::CastList()
{
    if(this->value == NULL || this->type != LIST)
        return std::nullopt;
    return *static_cast<Sojson::Node::List*>(this->value);
}

std::optional<Sojson::Node::Table> Sojson::Node::CastTable()
{
    if(this->value == NULL || this->type != TABLE)
        return std::nullopt;
    return *static_cast<Sojson::Node::Table*>(this->value);
}