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