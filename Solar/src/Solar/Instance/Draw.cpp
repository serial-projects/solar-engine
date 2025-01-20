#include "Solar/Instance/Draw.hpp"

void Solar::InstanceDraw(
    Solar::Instance* instance
)
{
    /* Draw the window: */
    Progator::Base::RendererClear(
        &instance->shared_core.graphics.renderer,
        0x00000000
    );
    Progator::Base::RendererDraw(
        &instance->shared_core.graphics.renderer
    );
}