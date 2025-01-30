#include "Solar/Modes/Scene/Mode/Draw.hpp"
#include "Solar/Core/Provider.hpp"

#include <iostream>

void Solar::Modes::Scene::ModeDraw(
    Solar::Modes::Scene::Mode* mode
)
{
    /* NOTE: grab the main display (or unit) to renderer: */
    Solar::Core::Graphics::Unit* main_unit =
        Solar::Core::Graphics::UnitsGetMainUnit(&mode->shared->units);

    /* Frame: */
    Progator::Base::RendererUse(main_unit->renderer);
    Progator::Base::RendererClear(main_unit->renderer, 0x00000000);

    /* Draw things :) */
    Progator::Objects::Shader* shader = 
        Solar::Core::Provider::Load::Shader(
            &mode->shared->warehouse,
            "root:Shaders/Basic",
            "main"
        );
    Progator::Objects::Mesh* mesh = 
        Solar::Core::Provider::Load::Mesh(
            &mode->shared->warehouse,
            "root:Meshes/Square",
            "Square.*",
            "main"
        );
    
    Progator::Objects::MeshDraw(mesh, main_unit->renderer);
    Progator::Objects::ShaderUse(shader, main_unit->renderer);

    Progator::Base::RendererDraw(main_unit->renderer);
}