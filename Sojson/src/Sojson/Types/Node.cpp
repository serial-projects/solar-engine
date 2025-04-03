#include "Sojson/Types/Node.hpp"

inline Sojson::Types::Basic::Result Sojson::Node::Is(
    Sojson::Node::NodeTypes type
)
{
    return this->type == type;
}

void Sojson::Node::Iterate(
    std::function<void(Sojson::Node*)> iterator
)
{
    iterator(this);
    switch(this->type)
    {
        case LIST:
            {
                Sojson::Node::List* list_value = static_cast<Sojson::Node::List*>(this->value);
                for(Sojson::Node* node : *list_value)
                    node->Iterate(iterator);
            };
            break;
        case TABLE:
            {
                Sojson::Node::Table* table_value = static_cast<Sojson::Node::Table*>(this->value);
                for(auto& content : *table_value)
                    content.second->Iterate(iterator);
            };
            break;
    };
}

void Sojson::Node::Cleanup()
{
    switch(this->type)
    {
        case Sojson::Node::INTEGER:
            delete static_cast<Sojson::Node::Integer*>(this->value);
            break;
        case Sojson::Node::DECIMAL:
            delete static_cast<Sojson::Node::Decimal*>(this->value);
            break;
        case Sojson::Node::STRING:
            delete static_cast<Sojson::Node::String*>(this->value);
            break;
        case Sojson::Node::NOTHING:
            /* NULL values: */
            break;
        case Sojson::Node::BOOLEAN:
            delete static_cast<Sojson::Node::Boolean*>(this->value);
            break;
        /**
         * Here is performed more complex cleanup, but it follows the same, we get the value on
         * the table or list and do a recursive cleanup and then free the memory.
         */
        case Sojson::Node::LIST:
            {
                Sojson::Node::List* list_value = static_cast<Sojson::Node::List*>(this->value);
                for(Sojson::Node* value : *list_value)
                {
                    value->Cleanup();
                    delete value;
                }
                delete static_cast<Sojson::Node::List*>(this->value);
            };
            break;
        case Sojson::Node::TABLE:
            {
                Sojson::Node::Table* table_value = static_cast<Sojson::Node::Table*>(this->value);
                for(auto& content : *table_value)
                {
                    content.second->Cleanup();
                    delete content.second;
                }
                delete static_cast<Sojson::Node::Table*>(this->value);
            };
            break;
        default:
            /* XXX: This is impossible of ever happening! */
            std::abort();
    };
    this->type  = Sojson::Node::NOTHING;
    this->value = nullptr;
}

Sojson::Node::Node()
{
    this->type  = Sojson::Node::NOTHING;
    this->value = nullptr;
}

Sojson::Node::~Node()
{
    this->Cleanup();
}