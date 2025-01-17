#ifndef FeraMeshingMesh_hpp
#define FeraMeshingMesh_hpp

#include "Fera/Meshing/MeshUnit.hpp"

namespace Fera
{
    namespace Meshing
    {
        /// @brief The MeshUnit* is also an Mesh, since everything has a root.
        typedef Fera::Meshing::MeshUnit Mesh;
        Fera::Meshing::Mesh* MeshNew();
        void MeshDestroy(Fera::Meshing::MeshUnit* mesh_unit);
        void MeshInit(Fera::Meshing::MeshUnit* mesh_unit);
    };
};

#endif