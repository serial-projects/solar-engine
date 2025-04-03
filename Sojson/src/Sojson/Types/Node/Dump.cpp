#include "Sojson/Types/Node.hpp"

Sojson::Types::Basic::String Sojson::Node::Dump()
{
    Sojson::Types::Basic::String buffer;
    switch(this->type)
    {
        /* Basic Ways to read the nodes: */
        case INTEGER:
            buffer = std::to_string(*static_cast<Sojson::Node::Integer*>(this->value));
            break;
        case DECIMAL:
            buffer = std::to_string(*static_cast<Sojson::Node::Decimal*>(this->value));
            break;
        case STRING:
            buffer = "\"" + (*static_cast<Sojson::Node::String*>(this->value)) + "\"";
            break;
        case NOTHING:
            buffer = "null";
            break;
        case BOOLEAN:
            buffer = *static_cast<Sojson::Node::Boolean*>(this->value) ? "true" : "false";
            break;
        /* More complex ways to read the nodes in a recursive manner: */
        case LIST:
            {
                Sojson::Node::List* list_value = static_cast<Sojson::Node::List*>(this->value);
                buffer = "[";
                for(auto it = list_value->begin(); it != list_value->end(); it++)
                {
                    Sojson::Node* indexing_value = *it;
                    buffer += indexing_value->Dump();
                    if(std::next(it) != list_value->end())
                        buffer += ", ";
                }
                buffer += "]";
            };
            break;
        case TABLE:
            {
                Sojson::Node::Table* table_value = static_cast<Sojson::Node::Table*>(this->value);
                buffer = "{";
                for(auto content = table_value->begin(); content != table_value->end(); content++)
                {
                    Sojson::Node* indexing_node = content->second;
                    buffer += "\"" + content->first + "\": ";
                    buffer += indexing_node->Dump();
                    if(std::next(content) != table_value->end())
                        buffer += ", ";
                }
                buffer += "}";
            };
            break;
        default:
            /* NOTE: invalid type. */
            std::abort();
            break;
    };
    return buffer;
}

