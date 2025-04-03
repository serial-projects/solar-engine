#include "Sojson/Decode/Instance.hpp"
#include "Sojson/Decode/Is.hpp"

/**
 * TODO: account for stoi, stof errors;
 * TODO: account for string errors.
 */

Sojson::Node* Sojson::Decode::Instance::GetBasicValue(
    Logica::Types::Basic::String& key
)
{
    Sojson::Decode::Is::Types type  = Sojson::Decode::Is::TokenType(key);
    Sojson::Node* building_node     = new Sojson::Node;
    switch(type)
    {
        case Sojson::Decode::Is::Types::Integer:
            building_node->SetIntegerValue(std::stoi(key));
            break;
        case Sojson::Decode::Is::Types::Decimal:
            building_node->SetDecimalValue(std::stof(key));
            break;
        case Sojson::Decode::Is::Types::String:
            building_node->SetStringValue(key.substr(1, key.size() - 2));
            break;
        case Sojson::Decode::Is::Types::Boolean:
            building_node->SetBooleanValue((key == "yes" || key == "true") ? 1 : 0);
            break;
        case Sojson::Decode::Is::Types::Null:
            building_node->SetNullValue();
            break;
        default:
            {
                this->validator.ReportError(
                    Sojson::Decode::Instance::INVALID_TOKEN,
                    "At line: %d, got an invalid token = %s",
                    this->tokenizer_instance.GetCurrentLine(),
                    key.c_str()
                );
                this->state = Sojson::Decode::Instance::DIED;
            };
            break;
    };
    return building_node;
}