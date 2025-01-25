#include "Solar/Instance/Tick.hpp"

#include <iostream>

void Solar::InstanceTick(
    Solar::Instance* instance
)
{
    /* Pump the events: */
    Solar::Modes::Scene::ModeTick(&instance->scene_mode);

    /* Increment the tick counter: */
    if(instance->shared_core.basics.tick_counter % 100 == 0)
    {
        std::cout
            << __PRETTY_FUNCTION__
            << ": TC = "
            << instance->shared_core.basics.tick_counter
            << " | DC = " 
            << instance->shared_core.basics.draw_counter
            << "\n"
            << __PRETTY_FUNCTION__
            << ": TC (Rate) = "
            << (int)instance->shared_core.basics.tick_rate
            << "/s | DC (Rate) = "
            << (int)instance->shared_core.basics.draw_rate
            << "/s\n";
    }
    ++instance->shared_core.basics.tick_counter;
}