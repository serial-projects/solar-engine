#ifndef ProgatorBackendsOpenGLMesh_hpp
#define ProgatorBackendsOpenGLMesh_hpp

#include "Progator/Backends/OpenGL/Basics.hpp"
#include "Progator/Validator.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            typedef struct Mesh
            {
                Progator::Backends::OpenGL::VBO vbo;
                Progator::Backends::OpenGL::VAO vao;
                Progator::Validator* validator;
                Progator::U32 amount;
            } Mesh;
            Progator::Backends::OpenGL::Mesh* MeshNew();
            void MeshDestroy(Progator::Backends::OpenGL::Mesh* mesh);
            void MeshInit(Progator::Backends::OpenGL::Mesh* mesh, Progator::Validator* validator);
            void MeshLoadVerTexNor(Progator::Backends::OpenGL::Mesh* mesh, Progator::F32 data[], const Progator::U32 amount);
            void MeshDraw(Progator::Backends::OpenGL::Mesh* mesh);
        };
    };
};

#endif