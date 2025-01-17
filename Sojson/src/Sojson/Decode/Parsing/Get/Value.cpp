#include "Sojson/Decode/Parsing/Get/Value.hpp"
#include "Sojson/Decode/Parsing/Get/Basic.hpp"
#include "Sojson/Decode/Parsing/Get/Table.hpp"
#include "Sojson/Decode/Parsing/Get/List.hpp"

Sojson::Node* Sojson::Decode::Parsing::Get::Value(
    Sojson::Decode::Instance* instance,
    const Sojson::Types::String token,
    const Sojson::Types::U8 depth
)
{
    Sojson::Node* value = nullptr;
    if(token == "{")
        value = Sojson::Decode::Parsing::Get::Table(instance, depth);
    else if(token == "[")
        value = Sojson::Decode::Parsing::Get::List(instance, depth);
    else
        value = Sojson::Decode::Parsing::Get::BasicValueFromToken(instance, token);
    return value;
}

Sojson::Node* Sojson::Decode::Parsing::Get::ValueRoot(
    Sojson::Decode::Instance* instance
)
{
    /* TODO: this might be wrong but on empty files, this will fail! */
    return Sojson::Decode::Parsing::Get::Value(
        instance,
        instance->current_tokenizer.GetToken(false),
        0
    );
}