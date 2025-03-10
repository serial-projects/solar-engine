#include "Solar/Core/Provider/Load/Helpers/Mesh/Build.hpp"

Progator::Objects::Mesh* Solar::Core::Provider::Load::Helpers::Mesh::Build(
    Solar::Core::Graphics::Unit* rendering_unit,
    Fera::Meshing::MeshUnitTypes::Object& object,
    Solar::Core::Provider::Load::Helpers::Mesh::Layouts& layouts
)
{
    Progator::Objects::Mesh* mesh = new Progator::Objects::Mesh();
    
    Progator::Objects::MeshInit(
        mesh,
        &rendering_unit->pointers,
        rendering_unit->renderer,
        &rendering_unit->validator
    );

    /* buffer the data: */
    Progator::Objects::MeshSetBuffer(
        mesh,
        rendering_unit->renderer,
        object.data(),
        object.size()
    );

    /* set the layouts: */
    Solar::Types::Basic::U8 layout_counter = 0;
    for(
        Solar::Types::Basic::U8 index=0;
        index < layouts.size() && index < UINT8_MAX;
        ++index
    )
    {
        Progator::Objects::MeshSetLayout(
            mesh,
            rendering_unit->renderer,
            layouts.at(index)
        );
        Progator::Objects::MeshEnableLayout(
            mesh,
            rendering_unit->renderer,
            index
        );
        /* here, count the layout for the final SetVertices() function. */
        layout_counter += layouts.at(index).size;
    }

    /* set the vertices: */
    Progator::Objects::MeshSetVertices(
        mesh,
        rendering_unit->renderer,
        layout_counter
    );

    /* done: */
    return mesh;
}