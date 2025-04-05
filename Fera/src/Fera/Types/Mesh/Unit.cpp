#include "Fera/Types/Mesh.hpp"

Fera::Types::Mesh::Unit::Unit()
{
    this->data = Fera::Types::Mesh::Unit::Data();
    this->faces= 0;
}

Fera::Types::Mesh::Unit::~Unit()
{

}