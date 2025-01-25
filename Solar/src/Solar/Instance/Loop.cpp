#include "Solar/Instance/Loop.hpp"
#include "Solar/Instance/Tick.hpp"
#include "Solar/Instance/Draw.hpp"

void Solar::InstanceLoop(
    Solar::Instance* instance
)
{
    const Solar::Types::Basic::U64 start_age = SDL_GetTicks64();
    Solar::Types::Basic::U64 last_tick = start_age;
    Solar::Types::Basic::U64 tick_delta= 0;
    Solar::Types::Basic::U64 last_draw = start_age;
    Solar::Types::Basic::U64 draw_delta= 0;
    Solar::Types::Basic::U64 now       = start_age;
    while(instance->shared_core.basics.state != 0)
    {
        now = SDL_GetTicks64();

        /* for tick: */
        tick_delta = (now - last_tick);
        if(tick_delta >= (1000.0f / instance->shared_core.basics.tick_rate))
        {
            Solar::InstanceTick(instance);
            last_tick = now;
        }

        /* for draw: */
        if(instance->shared_core.basics.draw_rate >= 1)
        {
            draw_delta = (now - last_draw);
            if(draw_delta >= (1000.0f / instance->shared_core.basics.draw_rate))
            {
                Solar::InstanceDraw(instance);
                last_draw = now;
            }
        }
        else
            Solar::InstanceDraw(instance);
    }
}