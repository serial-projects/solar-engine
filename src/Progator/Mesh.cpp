#include "Progator/Mesh.hpp"

Progator::Mesh* Progator::MeshNew()
{
    Progator::Mesh* proto = new Progator::Mesh;
    return proto;
}

void Progator::MeshDestroy(Progator::Mesh* mesh)
{
    mesh->pointers->mesh_destroy(mesh->backend);
    delete mesh;
}

void Progator::MeshInit(Progator::Mesh* mesh, Progator::Pointers* pointers, Progator::Validator* validator)
{
    mesh->validator = validator;
    mesh->pointers = pointers;
    
    mesh->backend = mesh->pointers->mesh_new();
    mesh->pointers->mesh_init(mesh->backend, mesh->validator);
}

void Progator::MeshLoadVerTexNor(Progator::Mesh* mesh, const Progator::F32 data[], const Progator::U32 amount)
{
    mesh->pointers->mesh_load_vertexnor(
        mesh->backend,
        data,
        amount
    );
}

void Progator::MeshDraw(Progator::Mesh* mesh)
{
    mesh->pointers->mesh_draw(
        mesh->backend
    );
}