#ifndef solar_core_shared_hxx
#define solar_core_shared_hxx

#include "Solar/Core/Window.hxx"
#include "Solar/Core/Storage.hxx"
#include "Solar/Types.hxx"

namespace Solar
{
    namespace Core
    {
        struct Shared
        {
            Solar::Core::Window::BasicSDLWindow window;
            Solar::Core::Storage::ContentProvider content_provider;
            Solar::Types::U8  mode = 0b10000000;
            Solar::Types::U64 tick_counter = 0;
            Solar::Types::U64 draw_counter = 0;
            Solar::Types::U16 framerate = 120;
        };
    };
};

#endif
// Solar/Core/Shared.hxx: