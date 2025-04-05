#include "Fera/Types/Mesh.hpp"

Fera::Types::Mesh::Value::Value()
{
    this->type = Fera::Types::Mesh::Value::Types::NOTHING;
    this->value= nullptr;
}

Fera::Types::Mesh::Value::~Value()
{
    switch(this->type)
    {
        case Fera::Types::Mesh::Value::Types::GROUP:
            {
                Fera::Types::Mesh::Value::Group* current_group = 
                    static_cast<Fera::Types::Mesh::Value::Group*>(this->value);
                for(auto& content : *current_group)
                    delete content.second;
                delete static_cast<Fera::Types::Mesh::Value::Group*>(this->value);
            };
            break;
        case Fera::Types::Mesh::Value::Types::UNIT:
            {
                delete static_cast<Fera::Types::Mesh::Value::Unit*>(this->value);
            };
            break;
    };
}

Fera::Types::Basic::String Fera::Types::Mesh::Value::Dump(
    const Fera::Types::Basic::String& key,
    std::vector<Fera::Types::Basic::String>* location_stack
)
{
    location_stack->push_back(key);
        Fera::Types::Basic::String buffer;
        for(
            Fera::Types::Basic::U8 index=0;
            index < UINT8_MAX && index < location_stack->size();
            index++
        )
        {
            buffer  = ("\t" + buffer);
            buffer += location_stack->at(index);
            buffer += (index > (location_stack->size() - 2)) ? "" : ".";
        }
        buffer += ": ";
        switch(this->type)
        {
            case Fera::Types::Mesh::Value::Types::GROUP:
                {
                    buffer += "GROUP\n";
                    Fera::Types::Mesh::Value::Group* current_group =
                        static_cast<Fera::Types::Mesh::Value::Group*>(this->value);
                    for(auto& content : *current_group)
                        buffer += content.second->Dump(content.first, location_stack);
                };
                break;
            case Fera::Types::Mesh::Value::Types::UNIT:
                {
                    buffer += "UNIT: ";
                    Fera::Types::Mesh::Value::Unit* current_unit =
                        static_cast<Fera::Types::Mesh::Value::Unit*>(this->value);
                    buffer += (
                        "Data Size: "   + std::to_string(current_unit->data.size()) + 
                        ", Faces: "       + std::to_string(current_unit->faces) +
                        "\n"
                    );
                };
                break;
            default:
                {
                    buffer += "NOTHING\n";
                }
                break;
        }
    location_stack->pop_back();
    return buffer;
}