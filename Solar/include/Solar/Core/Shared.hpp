#ifndef SolarCoreShared_hpp
#define SolarCoreShared_hpp

#include "Solar/Core/Basics.hpp"
#include "Solar/Core/Graphics.hpp"
#include "Solar/Core/Provider.hpp"

namespace Solar
{
    namespace Core
    {
        /// @brief Those are variables that are meant to be shared across all the instance modes 
        /// like configuration screen, scene mode, etc.
        struct Shared
        {
            /// @brief contain instance information like state, tick_counter, etc.
            Solar::Core::Basics             basics;

            /// @brief contain all the units.
            Solar::Core::Graphics::Units    units;

            /// @brief contains all the packages.
            Solar::Core::Provider::Warehouse warehouse;

            /// @brief contain the validator.
            Logica::Control::Validator      validator;
        };

        Solar::Core::Shared SharedNew();
        void SharedDestroy(Solar::Core::Shared* shared);
        void SharedInit(Solar::Core::Shared* shared);
    };
};

#endif