#include "Fera/Backends/OBJ/Decode.hpp"

Fera::Types::Mesh* Fera::Backends::OBJ::Decode::GetMesh()
{
    /**
     * NOTE: This will dereference an pointer by another point. You must keep track of the past
     * allocated meshes or it will do a huge memory!
     */
    this->building_mesh = new Fera::Types::Mesh;
    this->globals.vertices.clear();
    this->globals.uv.clear();
    this->globals.vertices.clear();

    /** Set the current variables to the default state: */
    this->current_group         = "root";
    this->current_object        = "default";

    /** Start to parse the code here: */
    
}