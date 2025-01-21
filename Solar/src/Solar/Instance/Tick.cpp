#include "Solar/Instance/Tick.hpp"

void Solar::InstanceTick(
    Solar::Instance* instance
)
{
    /* Pump the events: */
    Solar::Modes::Scene::ModeTick(&instance->scene_mode);
}