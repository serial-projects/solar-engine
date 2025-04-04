#include "Fera/Types/Mesh.hpp"

Fera::Types::Mesh::Mesh()
{
    /* The value is initialized here. */
    this->root = new Fera::Types::Mesh::Value;
}

Fera::Types::Mesh::~Mesh()
{
    /* NOTE: This value is initialized early.*/
    delete this->root;
}

Fera::Types::Mesh::Value* Fera::Types::Mesh::Get(const Logica::Texting::SplitResult& result)
{
    Fera::Types::Mesh::Value *current_value = this->root;
    Fera::Types::Mesh::Value *value = nullptr;
    Fera::Types::Basic::U8 index = 0;
    for(Fera::Types::Basic::U8 index = 0; index < UINT8_MAX; index++)
    {
        /* When the index is equal to size then:
         * It is the end of the list and we expect an Value to be on the end of the list;
         * If not, then it is simply another group! */
        if(index >= result.size())
        {
            if(current_value->type != Fera::Types::Mesh::Value::UNIT)
                value = current_value;
        }
        else
        {
            /* In this case, we also need to look for the case the current value is a 
             * UNIT, in case it is, we have a premature end search. We also look for the
             * lack of section, in case there is a lacking section then we just ignore
             * it. */
            if(current_value->type == Fera::Types::Mesh::Value::GROUP)
            {
                Fera::Types::Basic::String current_token = result.at(index);
                Fera::Types::Mesh::Value::Group* value = 
                    static_cast<Fera::Types::Mesh::Value::Group*>(current_value->value);
                if(value->find(current_token) != value->end())
                    current_value = value->at(current_token);
                else
                    break;
            }
            else
                break;
        }
    }
    return value;
}


Fera::Types::Mesh::Value* Fera::Types::Mesh::Get(const Fera::Types::Basic::String& key)
{
    Logica::Texting::SplitResult result = Logica::Texting::Split(key, '.');
    return this->Get(result);
}

Fera::Types::Mesh::Value* Fera::Types::Mesh::Get(const Fera::Types::Basic::CH8* key)
{
    return this->Get(Fera::Types::Basic::String(key));
}