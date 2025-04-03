#include "Sojson/Types/Node.hpp"

void Sojson::Node::SetIntegerValue(
    const Sojson::Node::Integer value
)
{
    this->type = INTEGER;
    this->value= static_cast<void*>(new Sojson::Node::Integer);
    *(static_cast<Sojson::Node::Integer*>(this->value)) = value;
}

void Sojson::Node::SetDecimalValue(
    const Sojson::Node::Decimal value
)
{
    this->type = DECIMAL;
    this->value= static_cast<void*>(new Sojson::Node::Decimal);
    *(static_cast<Sojson::Node::Decimal*>(this->value)) = value;
}

void Sojson::Node::SetStringValue(
    const Sojson::Node::String& value
)
{
    this->type = STRING;
    this->value= static_cast<void*>(new Sojson::Node::String);
    *(static_cast<Sojson::Node::String*>(this->value)) = value;
}

void Sojson::Node::SetBooleanValue(
    const Sojson::Node::Boolean value
)
{
    this->type = BOOLEAN;
    this->value= static_cast<void*>(new Sojson::Node::Boolean);
    *(static_cast<Sojson::Node::Boolean*>(this->value)) = value;
}

void Sojson::Node::SetNullValue()
{
    this->type = NOTHING;
    this->value= nullptr;
}

Sojson::Node::List* Sojson::Node::CreateList()
{
    this->type = LIST;
    this->value= static_cast<void*>(new Sojson::Node::List);
    return static_cast<Sojson::Node::List*>(this->value);
}

Sojson::Node::Table* Sojson::Node::CreateTable()
{
    this->type = TABLE;
    this->value= static_cast<void*>(new Sojson::Node::Table);
    return static_cast<Sojson::Node::Table*>(this->value);
}