#ifndef ProgatorBackendsOpenGLMesh_hpp
#define ProgatorBackendsOpenGLMesh_hpp

#include "Progator/Types.hpp"
#include "Progator/Backends/OpenGL/Types.hpp"
#include "Progator/Backends/OpenGL/Renderer.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            struct Mesh
            {
                Progator::Backends::OpenGL::Types::VertexBufferObject vbo;
                Progator::Backends::OpenGL::Types::VertexAttributeObject vao;
                Progator::Types::Basic::U64 vertices;
            };
            Progator::Backends::OpenGL::Mesh* MeshNew();
            void MeshDestroy(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer);
            void MeshInit(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer, Logica::Control::Validator* validator);
            void MeshSetBuffer(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::F32* data, const Progator::Types::Basic::U32 size);
            void MeshSetLayout(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Specifics::Mesh::Layout layout);
            void MeshEnableLayout(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::U8 layout);
            void MeshDisableLayout(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::U8 layout);
            void MeshSetVertices(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::U64 size);
            void MeshDraw(Progator::Backends::OpenGL::Mesh* mesh, Progator::Backends::OpenGL::Renderer* renderer);
        };
    };
};

#endif