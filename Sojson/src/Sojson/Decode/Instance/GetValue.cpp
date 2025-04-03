#include "Sojson/Decode/Instance.hpp"

Sojson::Node* Sojson::Decode::Instance::GetRootValue()
{
    Logica::Types::Basic::String early_key;
    this->tokenizer_instance.GetToken(&early_key);
    return this->GetValue(early_key, 0);
}

Sojson::Node* Sojson::Decode::Instance::GetValue(
    Logica::Types::Basic::String& key,
    const Logica::Types::Basic::U8 depth
)
{
    Sojson::Node* building_node = nullptr;
    if(key == "{")      building_node = this->GetTable(depth);
    else if(key == "[") building_node = this->GetList(depth);
    else                building_node = this->GetBasicValue(key);
    return building_node;
}