#include "Fera/Meshing/Mesh.hpp"

Fera::Meshing::Mesh* Fera::Meshing::MeshNew()
{
    Fera::Meshing::Mesh* mesh = new Fera::Meshing::Mesh;
    return mesh;
}

void Fera::Meshing::MeshDestroy(
    Fera::Meshing::MeshUnit* mesh_unit
)
{
    Fera::Meshing::MeshUnitDestroy(mesh_unit);
}

static inline Fera::Meshing::MeshUnitTypes::Group* __FeraMeshingMeshUnitTypesGroupNewGroup()
{
    Fera::Meshing::MeshUnitTypes::Group* new_group = new Fera::Meshing::MeshUnitTypes::Group;
    return new_group;
}

void Fera::Meshing::MeshInit(
    Fera::Meshing::MeshUnit* mesh_unit
)
{
    mesh_unit->type = Fera::Meshing::MeshUnitValueTypes::Group;
    mesh_unit->value = (void*)__FeraMeshingMeshUnitTypesGroupNewGroup();
}