#include "Sojson/Types/Node.hpp"

Sojson::Node* Sojson::Node::Get(
    Sojson::Types::Basic::String& key
)
{
    Logica::Texting::SplitResult split_result = 
        Logica::Texting::Split(key, '.');
    return this->Get(split_result, 0);
}

Sojson::Node* Sojson::Node::Get(
    const Sojson::Types::Basic::CH8* key
)
{
    Sojson::Types::Basic::String __key = Sojson::Types::Basic::String(key);
    return this->Get(__key);
}

Sojson::Node* Sojson::Node::Get(
    const Logica::Texting::SplitResult& key,
    const Logica::Types::Basic::U8 depth
)
{
    Sojson::Node* current_node = nullptr;
    if(depth >= key.size())
    {
        current_node = this;
    }
    else
    {
        /* Keep searching in this case: */
        if(this->type == TABLE)
        {
            Sojson::Node::Table* table = static_cast<Sojson::Node::Table*>(this->value);
            Logica::Types::Basic::String current_key = key.at(depth);
            if(table->find(current_key) != table->end())
            {
                Sojson::Node* next_node = table->at(current_key);
                current_node = next_node->Get(key, depth + 1);
            }
        }
    }
    return current_node;
}