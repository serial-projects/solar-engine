#ifndef SolarCoreBasics_hpp
#define SolarCoreBasics_hpp

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Core
    {
        struct Basics
        {
            Solar::Types::Basic::U8     state;
            Solar::Types::Basic::U8     tick_rate;
            Solar::Types::Basic::U8     draw_rate;
            Solar::Types::Basic::U64    tick_counter;
            Solar::Types::Basic::U64    draw_counter;
        };
        Solar::Core::Basics BasicsNew();
        void BasicsDestroy(Solar::Core::Basics* basics);
        void BasicsInit(Solar::Core::Basics* basics);
    };
};

#endif