#ifndef SolarCoreShared_hpp
#define SolarCoreShared_hpp

#include "Solar/Core/Basics.hpp"
#include "Solar/Core/Graphics.hpp"

namespace Solar
{
    namespace Core
    {
        /// @brief Those are variables that are meant to be shared across all the instance modes 
        /// like configuration screen, scene mode, etc.
        struct Shared
        {
            /// @brief contain instance information like state, tick_counter, etc.
            Solar::Core::Basics     basics;
            Solar::Core::Graphics   graphics;
        };
        Solar::Core::Shared SharedNew();
        void SharedDestroy(Solar::Core::Shared* shared);
        void SharedInit(Solar::Core::Shared* shared);
    };
};

#endif