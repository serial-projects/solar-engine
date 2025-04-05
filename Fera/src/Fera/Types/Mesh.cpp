#include "Fera/Types/Mesh.hpp"

Fera::Types::Mesh::Mesh()
{
    /**
     * NOTE: In all the cases, we want the first value to be simply an group, why?
     * most of the objects are categorized on trees anyway.
     */
    this->root          = new Fera::Types::Mesh::Value;
    this->root->type    = Fera::Types::Mesh::Value::Types::GROUP;
    this->root->value   = static_cast<void*>(new Fera::Types::Mesh::Value::Group);
}

Fera::Types::Mesh::~Mesh()
{
    /* NOTE: This value is initialized early.*/
    delete this->root;
}

Fera::Types::Basic::String Fera::Types::Mesh::Dump()
{
    std::vector<Fera::Types::Basic::String> location_stack;
    return "\n" + this->root->Dump(Fera::Types::Basic::String("root"), &location_stack);
}