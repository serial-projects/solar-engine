#ifndef solar_core_shared_hxx
#define solar_core_shared_hxx

#include "Solar/Core/Window.hxx"
#include "Solar/Core/Storage.hxx"
#include "Solar/Types.hxx"

#define SolarCoreSharedMode_GetRunning(mode)    (mode >> 7)
#define SolarCoreSharedMode_ToggleRunning(mode) mode ^= 0b10000000;
#define SolarCoreSharedMode_Shutdown(mode)      mode = 0

#define SolarCoreSharedMode_GetDoDraw(mode)     (mode & 0b01000000)
#define SolarCoreSharedMode_ToggleDoDraw(mode)  mode ^= 0b01000000

#define SolarCoreSharedMode_GetDoTick(mode)     (mode & 0b00100000)
#define SolarCoreSharedMode_ToggleDoTick(mode)  mode ^= 0b00100000

#define SolarCoreSharedMode_GetGDebug(mode)     (mode & 0b00010000)
#define SolarCoreSharedMode_ToggleGDebug(mode)  mode ^= 0b00010000

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