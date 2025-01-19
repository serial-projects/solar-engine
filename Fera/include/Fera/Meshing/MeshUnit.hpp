#ifndef FeraMeshingMeshUnit_hpp
#define FeraMeshingMeshUnit_hpp

#include "Fera/Types.hpp"

/*
 * NOTE: this is a MESHING for Solar Engine, in Solar Engine, we only care for the raw data to work
 * On the engine later, that mean for example, animations and etc, are done on the manifest file
 * itself rather than the .glTF or FBX, here we want to extract all the data we can to build an
 * vertex mesh with the layouts we want. The simplest is OBJ for example.
 * 
 * NOW, Solar Engine supports an layout that accept keys reference, for example:
 * Cube (which has LeftSide, RightSide, ...) the key to this reference is:
 * Default:Cube.LeftSide        -> this means Cube.LeftSide
 * Default:Cube.*               -> this means all elements from the group "Cube"
 * NOTE: this is done on ContentProvider::LoadMesh() key system.
 * 
 * This is derived from OBJ since: g -> all elements common to something, for example Cube
 * and o -> a single element, in a structure, this might be:
 * v        ...    
 * vt       ...
 * vn       ...
 * g Cube
 * o LeftSide
 * f        ...
 * o RightSide
 * f        ...
 * 
 * Q: Is this out the standards? 
 * A: Probably, but Solar Engine will use on the future scripts to build an own file for loading
 * models, this is just an workaround for now.
 * 
 * RESUME: basically:
 *  g-> groups  (contains objects)
 *  o-> objects (contains data)
 *
 * To simply, objects are MeshObjectUnit, which contains certain properties like buffer, beziers
 * and more, BUT! Do we support this all? Definitely not, maybe on the future? So, Object is nothing
 * but buffers!
 */

/* TODO: support bezier and advanced object stuff. */
/* TODO: maybe on the future, Fera v2? */

namespace Fera
{
    namespace Meshing
    {
        /// @brief Enumerate all the types of MeshUnit.
        namespace MeshUnitValueTypes
        {
            enum MeshUnitValueTypes
            {
                /// @brief Impossible values.
                Nothing = 0,

                /// @brief Basic Data, that is data already done to be drawn, an sequence of
                /// F32 ready to be put on the screen.
                Data,

                /// @brief When an object contains another subobject inside.
                Object,

                /// @brief When an group contains a subgroup.
                Group,

                /// @brief Impossible values.
                Unknown = UINT8_MAX
            };
        };
        
        struct MeshUnit
        {
            /* NOTE: do something else here: */
            void *value;
            Fera::Types::U8 type;
        };
        Fera::Meshing::MeshUnit* MeshUnitNew();
        void MeshUnitDestroy(Fera::Meshing::MeshUnit* mesh_unit);
        void MeshUnitInit(Fera::Meshing::MeshUnit* mesh_unit, void* value, const Fera::Types::U8 type);

        /// @brief All the typedefs for the types.
        namespace MeshUnitTypes
        {
            typedef std::vector<Fera::Types::F32> Buffer;
            typedef std::unordered_map<Fera::Types::String, Fera::Meshing::MeshUnit*> Group;
            typedef std::vector<Fera::Types::F32> Object;
        };
    };
};

#endif