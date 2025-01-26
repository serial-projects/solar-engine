#include "Progator/Backends/OpenGL/Mesh.hpp"

Progator::Backends::OpenGL::Mesh* Progator::Backends::OpenGL::MeshNew()
{
    Progator::Backends::OpenGL::Mesh* mesh = new Progator::Backends::OpenGL::Mesh;
    return mesh;
}

void Progator::Backends::OpenGL::MeshDestroy(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer
)
{
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
    delete mesh;
}

void Progator::Backends::OpenGL::MeshInit(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer,
    Logica::Control::Validator* validator
)
{
    glGenBuffers(1, &mesh->vbo);
    glGenVertexArrays(1, &mesh->vao);
    mesh->vertices = 0;
}

static inline void __ProgatorBackendsOpenGLMeshSetBuffers(
    Progator::Backends::OpenGL::Mesh* mesh
)
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindVertexArray(mesh->vao);
}

void Progator::Backends::OpenGL::MeshSetBuffer(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Basic::F32* data,
    const Progator::Types::Basic::U32 size
)
{
    __ProgatorBackendsOpenGLMeshSetBuffers(mesh);
    glBufferData(
        GL_ARRAY_BUFFER,
        size * sizeof(Progator::Types::Basic::F32),
        data,
        GL_STATIC_DRAW
    );
}

void Progator::Backends::OpenGL::MeshSetLayout(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Specifics::Mesh::Layout layout
)
{
    __ProgatorBackendsOpenGLMeshSetBuffers(mesh);
    GLsizei stride_result   = (GLsizei)(layout.stride_size) * (GLsizei)(layout.stride);
    void* layout_pointer    = (void*)(sizeof(Progator::Types::Basic::F32) * layout.padding);
    glVertexAttribPointer(
        (GLuint)(layout.id),
        (GLuint)(layout.size),
        GL_FLOAT,
        GL_FALSE,
        stride_result,
        layout_pointer
    );
    glEnableVertexAttribArray(layout.id);
}

void Progator::Backends::OpenGL::MeshEnableLayout(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Basic::U8 layout
)
{
    __ProgatorBackendsOpenGLMeshSetBuffers(mesh);
    glEnableVertexAttribArray(layout);
}

void Progator::Backends::OpenGL::MeshDisableLayout(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Basic::U8 layout
)
{
    __ProgatorBackendsOpenGLMeshSetBuffers(mesh);
    glDisableVertexAttribArray(layout);
}

void Progator::Backends::OpenGL::MeshSetVertices(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Basic::U64 size
)
{
    mesh->vertices = size;
}

void Progator::Backends::OpenGL::MeshDraw(
    Progator::Backends::OpenGL::Mesh* mesh,
    Progator::Backends::OpenGL::Renderer* renderer
)
{
    __ProgatorBackendsOpenGLMeshSetBuffers(mesh);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertices);
}