#ifndef ProgatorObjectsMesh_hpp
#define ProgatorObjectsMesh_hpp

#include "Progator/Types.hpp"
#include "Progator/Base/Renderer.hpp"
#include "Progator/Base/Pointers.hpp"

namespace Progator
{
    namespace Objects
    {
        struct Mesh
        {
            void* backend;
            Progator::Base::Pointers* pointers;
            Logica::Control::Validator* validator;
        };
        Progator::Objects::Mesh* MeshNew();
        void MeshDestroy(Progator::Objects::Mesh* mesh, Progator::Base::Renderer* renderer);
        void MeshInit(Progator::Objects::Mesh* mesh, Progator::Base::Pointers* pointers, Progator::Base::Renderer* renderer, Logica::Control::Validator* validator);
        void MeshSetBuffer(Progator::Objects::Mesh* mesh, Progator::Base::Renderer* renderer, const Progator::Types::Basic::F32* data, const Progator::Types::Basic::U32 size);
        void MeshSetLayout(Progator::Objects::Mesh* mesh, Progator::Base::Renderer* renderer, const Progator::Types::Specifics::Mesh::Layout layout);
        void MeshEnableLayout(Progator::Objects::Mesh* mesh, Progator::Base::Renderer* renderer, const Progator::Types::Basic::U8 layout);
        void MeshDisableLayout(Progator::Objects::Mesh* mesh, Progator::Base::Renderer* renderer, const Progator::Types::Basic::U8 layout);
        void MeshSetVertices(Progator::Objects::Mesh* mesh, Progator::Base::Renderer* renderer, const Progator::Types::Basic::U64 size);
        void MeshDraw(Progator::Objects::Mesh* mesh, Progator::Base::Renderer* renderer);
    };
};

#endif