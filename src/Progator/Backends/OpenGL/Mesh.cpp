#include "Progator/Backends/OpenGL/Mesh.hpp"

Progator::Backends::OpenGL::Mesh* Progator::Backends::OpenGL::MeshNew()
{
    Progator::Backends::OpenGL::Mesh* proto = new Progator::Backends::OpenGL::Mesh;
    return proto;
}

void Progator::Backends::OpenGL::MeshDestroy(Progator::Backends::OpenGL::Mesh* mesh)
{
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
    delete mesh;
}

void Progator::Backends::OpenGL::MeshInit(Progator::Backends::OpenGL::Mesh* mesh, Progator::Validator* validator)
{
    mesh->validator = validator;
    glGenBuffers(1, &mesh->vbo);
    glGenVertexArrays(1, &mesh->vao);
}

void Progator::Backends::OpenGL::MeshLoadVerTexNor(Progator::Backends::OpenGL::Mesh* mesh, const Progator::F32 data[], const Progator::U32 amount)
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindVertexArray(mesh->vao);

    /* NOTE: MeshLoadVerTexNor() only accepts triangles as inputs! */
    const Progator::U64 amount_data = sizeof(Progator::F32) * (amount * (3 + 2 + 3));

    glBufferData(GL_ARRAY_BUFFER, amount_data, data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) * sizeof(Progator::F32), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2 + 3) * sizeof(Progator::F32), (void*)(3 * sizeof(Progator::F32)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) * sizeof(Progator::F32), (void*)((3 + 2) * sizeof(Progator::F32)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    mesh->amount = amount;
}

void Progator::Backends::OpenGL::MeshDraw(Progator::Backends::OpenGL::Mesh* mesh)
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->amount);
}