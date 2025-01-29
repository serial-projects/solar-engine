#include "Fera/Meshing/MeshUnit.hpp"

Fera::Meshing::MeshUnit* Fera::Meshing::MeshUnitNew()
{
    Fera::Meshing::MeshUnit* mesh_unit = new Fera::Meshing::MeshUnit;
    return mesh_unit;
}

void Fera::Meshing::MeshUnitDestroy(
    Fera::Meshing::MeshUnit* mesh_unit
)
{
    switch(mesh_unit->type)
    {
        case Fera::Meshing::MeshUnitValueTypes::Nothing:
            /* Nothing allocated, then ignore: */
            break;
        case Fera::Meshing::MeshUnitValueTypes::Group:
            {
                /* GROUP means it is a group of MeshUnits! */
                Fera::Meshing::MeshUnitTypes::Group* group =
                    (Fera::Meshing::MeshUnitTypes::Group*)(mesh_unit->value);
                for(auto& content : *group)
                    Fera::Meshing::MeshUnitDestroy(content.second);
                delete (Fera::Meshing::MeshUnitTypes::Group*)(mesh_unit->value);
            };
            break;
        case Fera::Meshing::MeshUnitValueTypes::Object:
            /* TODO: support advanced mesh objects LOL. */
            {
                Fera::Meshing::MeshUnitTypes::Object* ov = 
                    (Fera::Meshing::MeshUnitTypes::Object*)(mesh_unit->value);
                delete ov;
            };
            break;
        case Fera::Meshing::MeshUnitValueTypes::Unknown:
        default:
            /* NOTE: if Unknown, then something very wrong happened. */
            std::abort();
            break;
    }
    delete mesh_unit;
}

void Fera::Meshing::MeshUnitInit(
    Fera::Meshing::MeshUnit* mesh_unit,
    void* value,
    const Fera::Types::U8 type
)
{
    mesh_unit->value = value;
    mesh_unit->type = type;
}