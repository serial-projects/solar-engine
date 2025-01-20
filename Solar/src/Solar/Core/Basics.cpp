#include "Solar/Core/Basics.hpp"

Solar::Core::Basics Solar::Core::BasicsNew()
{
    Solar::Core::Basics basics;
    return basics;
}

void Solar::Core::BasicsDestroy(
    Solar::Core::Basics* basics
)
{
    /* DO nothing, basics is on stack: */
    return;
}

void Solar::Core::BasicsInit(
    Solar::Core::Basics* basics
)
{
    basics->state       = 0b10000000;
    basics->tick_rate   = 60;
    basics->draw_rate   = 0;
    basics->tick_counter= 0;
    basics->draw_counter= 0;
}