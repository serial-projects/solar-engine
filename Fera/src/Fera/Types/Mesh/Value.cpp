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
                delete this->value;
            };
            break;
        case Fera::Types::Mesh::Value::Types::UNIT:
            {
                delete this->value;
            };
            break;
    };
}

Fera::Types::Basic::String Fera::Types::Mesh::Value::Dump()
{
    
}