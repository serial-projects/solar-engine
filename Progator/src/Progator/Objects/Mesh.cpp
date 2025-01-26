#include "Progator/Objects/Mesh.hpp"
Progator::Objects::Mesh* Progator::Objects::MeshNew()
{
    Progator::Objects::Mesh* mesh = new Progator::Objects::Mesh;
    return mesh;
}

void Progator::Objects::MeshDestroy(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Renderer* renderer
)
{
    mesh->pointers->mesh_destroy(mesh->backend, renderer->backend);
    delete mesh;
}

void Progator::Objects::MeshInit(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Pointers* pointers,
    Progator::Base::Renderer* renderer,
    Logica::Control::Validator* validator
)
{
    mesh->pointers = pointers;
    mesh->validator = validator;
    
    /* init: */
    mesh->backend = mesh->pointers->mesh_new();
    mesh->pointers->mesh_init(mesh->backend, renderer->backend, mesh->validator);
}

void Progator::Objects::MeshSetBuffer(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::F32* data,
    const Progator::Types::Basic::U32 size
)
{
    mesh->pointers->mesh_set_buffer(mesh->backend, renderer->backend, data, size);
}

void Progator::Objects::MeshSetLayout(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Specifics::Mesh::Layout layout
)
{
    mesh->pointers->mesh_set_layout(mesh->backend, renderer->backend, layout);
}

void Progator::Objects::MeshEnableLayout(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::U8 layout
)
{
    mesh->pointers->mesh_enable_layout(mesh->backend, renderer->backend, layout);
}

void Progator::Objects::MeshDisableLayout(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::U8 layout
)
{
    mesh->pointers->mesh_disable_layout(mesh->backend, renderer->backend, layout);
}

void Progator::Objects::MeshSetVertices(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::U64 size
)
{
    mesh->pointers->mesh_set_vertices(mesh->backend, renderer->backend, size);
}

void Progator::Objects::MeshDraw(
    Progator::Objects::Mesh* mesh,
    Progator::Base::Renderer* renderer
)
{
    mesh->pointers->mesh_draw(mesh->backend, renderer->backend);
}