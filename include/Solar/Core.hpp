#ifndef SolarCore_hpp
#define SolarCore_hpp

#include "Progator/Progator.hpp"
#include "Solar/Types.hpp"

namespace Solar
{
    typedef struct Core
    {
        /* PROGATOR modules: */
        Progator::Window* window;
        Progator::Renderer* renderer;
        Progator::Pointers* pointers;
        Progator::Validator* validator;

        /* Core environment: */
        Solar::U8   state;
        Solar::U8   framerate;
    } Core;

    Solar::Core* CoreNew();
    void CoreDestroy(Solar::Core* core);
    void CoreInit(Solar::Core* core);
    void CoreQuit(Solar::Core* core);
};

#endif