#ifndef ProgatorMesh_hpp
#define ProgatorMesh_hpp

#include "Progator/Types.hpp"
#include "Progator/Validator.hpp"
#include "Progator/Pointers.hpp"

namespace Progator
{
    typedef struct Mesh
    {
        void *backend;
        Progator::Pointers* pointers;
        Progator::Validator *validator;
    } Mesh;
    Progator::Mesh* MeshNew();
    void MeshDestroy(Progator::Mesh* mesh);
    void MeshInit(Progator::Mesh* mesh, Progator::Pointers* pointers, Progator::Validator* validator);
    void MeshLoadVerTexNor(Progator::Mesh* mesh, const Progator::F32 data[], const Progator::U32 amount);
    void MeshDraw(Progator::Mesh* mesh);
};

#endif