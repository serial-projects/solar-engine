#include "Solar/Modes/Scene/Mode/Draw.hpp"

void Solar::Modes::Scene::ModeDraw(
    Solar::Modes::Scene::Mode* mode
)
{
    /* NOTE: grab the main display (or unit) to renderer: */
    Solar::Core::Graphics::Unit* main_unit =
        Solar::Core::Graphics::UnitsGetMainUnit(&mode->shared->units);
    Progator::Base::RendererClear(main_unit->renderer, 0x00000000);
    Progator::Base::RendererDraw(main_unit->renderer);
}