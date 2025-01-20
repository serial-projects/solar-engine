#include "Solar/Instance/Loop.hpp"
#include "Solar/Instance/Tick.hpp"
#include "Solar/Instance/Draw.hpp"

void Solar::InstanceLoop(
    Solar::Instance* instance
)
{
    while(instance->shared_core.basics.state != 0)
    {
        Solar::InstanceTick(instance);
        Solar::InstanceDraw(instance);
    }
}