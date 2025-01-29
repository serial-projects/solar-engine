#include "Solar/Core/Provider/Load/Helpers/Mesh/Surf.hpp"
#include "Solar/Validator.hpp"

#include "Logica/Logica.hpp"
#include <iostream>

/* NOTE: here begins the game, you see:
 * Group.Object is the default pattern, for example, let's imagine an cube:
 * On OBJ: 'g' = group / 'o' = object
 * Cube/
 *      LeftSide/
 *      RightSide/
 *      ...
 * The cube itself is the group and the sides are the object (aka. the real buffers), but because
 * we should be able to access the cube itself, we can:
 *      Cube.LeftSide           -> this will show the left side of the cube.
 *      Cube.RightSide          -> this will show the right side of the cube.
 *      Cube.*                  -> this will show ALL the cube.
 *      Cube                    -> equivalent of 'Cube.*'
 *                              -> equivalent of '*' (this is due the implication of the dumb surf)
 * 
 * This parsing requires us to use an recursive way to build the list that results the final 
 * mesh (this will be result of the Surf function).
 */

/* TODO: implement '*' functionality! */

static Fera::Meshing::MeshUnitTypes::Object __SolarCoreProviderLoadHelpersMeshMergeAll(
    Fera::Meshing::MeshUnit* mesh_unit
)
{
    /* HERE we assume it is a group and we keep going to everywhere! */
    Fera::Meshing::MeshUnitTypes::Object result;
    if(mesh_unit->type == Fera::Meshing::MeshUnitValueTypes::Object)
    {
        result = *((Fera::Meshing::MeshUnitTypes::Object*)(mesh_unit->value));
    }
    else if(mesh_unit->type == Fera::Meshing::MeshUnitValueTypes::Group)
    {
        Fera::Meshing::MeshUnitTypes::Group* group =
            (Fera::Meshing::MeshUnitTypes::Group*)(mesh_unit->value);
        for(auto& content : *group)
        {
            Fera::Meshing::MeshUnitTypes::Object adquired_result =
                __SolarCoreProviderLoadHelpersMeshMergeAll(content.second);
            result.insert(
                result.end(),
                adquired_result.begin(),
                adquired_result.end()
            );
        }
    }
    return result;
}

static Fera::Meshing::MeshUnitTypes::Object __SolarCoreProviderLoadHelpersMeshSurfRecursive(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& object,
    const Logica::Data::String::SplitResult& path,
    Fera::Meshing::MeshUnit* mesh_unit,
    const Logica::Types::Basic::I8 index
)
{
    Fera::Meshing::MeshUnitTypes::Object building_object;
    if(mesh_unit->type == Fera::Meshing::MeshUnitValueTypes::Group)
    {
        /* LAST ONE: it is probably this case? Group.* (but * is omitted?) */
        if(index >= path.size())
        {
            building_object = __SolarCoreProviderLoadHelpersMeshMergeAll(mesh_unit);
        }
        else
        {
            /* For when there is a token, consider the following:
             * Group.* (on a group) = everything!
             * Group.Object = the object itself.
             */
            const Fera::Types::String current_group = path.at(index);
            if(current_group == "*")
            {
                building_object = __SolarCoreProviderLoadHelpersMeshMergeAll(mesh_unit);
            }
            else
            {
                Fera::Meshing::MeshUnitTypes::Group* group = 
                    (Fera::Meshing::MeshUnitTypes::Group*)(mesh_unit->value);
                if(group->find(current_group) == group->end())
                {
                    warehouse->validator.SetError(
                        Solar::ValidatorCodes::WarehouseMeshNotFound,
                        "on object: %s, not found: %s",
                        object.c_str(),
                        path.at(index).c_str()
                    );
                }
                else
                {
                    Fera::Meshing::MeshUnit* next = group->at(current_group);
                    building_object = __SolarCoreProviderLoadHelpersMeshSurfRecursive(
                        warehouse,
                        object,
                        path,
                        next,
                        index + 1
                    );
                }
            }
        }
    }
    else if(mesh_unit->type == Fera::Meshing::MeshUnitValueTypes::Object)
    {
        if(index == path.size())
        {
            building_object = *((Fera::Meshing::MeshUnitTypes::Object*)(mesh_unit->value));
        }
        else
        {
            warehouse->validator.SetError(
                Solar::ValidatorCodes::WarehouseMeshNotFound,
                "on object: %s, \"%s\" is an OBJECT, it cannot have subobjects",
                object.c_str(),
                path.at(index).c_str()
            );
            goto skip_due_bad;
        }
    }

    skip_due_bad:
    return building_object;
}

static Fera::Meshing::MeshUnitTypes::Object __SolarCoreProviderLoadHelpersMeshSurfBegin(
    Solar::Core::Provider::Warehouse* warehouse,
    const Solar::Types::Basic::String& object,
    const Logica::Data::String::SplitResult& path,
    Fera::Meshing::Mesh* mesh
)
{
    /* NOTE: we NEED the first group to kick start it aligned. 
     * but * -> wildcard for all
     * anything else: NOPE and keep parsing. 
     */
    Fera::Meshing::MeshUnitTypes::Object building_object;
    
    const Logica::Types::Basic::String early_group = path.at(0);
    Fera::Meshing::MeshUnitTypes::Group* root_group = 
        (Fera::Meshing::MeshUnitTypes::Group*)(mesh->value);
    if(root_group->find(early_group) == root_group->end())
    {
        warehouse->validator.SetError(
            Solar::ValidatorCodes::WarehouseMeshNotFound,
            "on object: %s, not found: %s",
            object.c_str(),
            early_group.c_str()
        );
    }
    else
    {
        Fera::Meshing::MeshUnit* next = root_group->at(early_group);
        building_object = __SolarCoreProviderLoadHelpersMeshSurfRecursive(
            warehouse,
            object,
            path,
            next,
            1
        );
    }

    return building_object;
}

Fera::Meshing::MeshUnitTypes::Object Solar::Core::Provider::Load::Helpers::Mesh::Surf(
    Solar::Core::Provider::Warehouse* warehouse,
    Fera::Meshing::Mesh* mesh,
    const Solar::Types::Basic::String& object
)
{
    Logica::Data::String::SplitResult path = Logica::Data::String::Split(object, '.');
    return __SolarCoreProviderLoadHelpersMeshSurfRecursive(
        warehouse,
        object,
        path,
        mesh,
        0
    );
}