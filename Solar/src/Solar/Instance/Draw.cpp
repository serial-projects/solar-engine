#include "Solar/Instance/Draw.hpp"
#include <iostream>

void Solar::InstanceDraw(
    Solar::Instance* instance
)
{
    /* Draw the window: */
    Solar::Modes::Scene::ModeDraw(&instance->scene_mode);

    /* Increment draw counter: */
    ++instance->shared_core.basics.draw_counter;
}