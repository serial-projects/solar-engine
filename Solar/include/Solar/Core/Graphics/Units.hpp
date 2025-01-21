#ifndef SolarCoreGraphicsUnits_hpp
#define SolarCoreGraphicsUnits_hpp

#include "Solar/Types.hpp"
#include "Solar/Core/Graphics/Unit.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Graphics
        {
        /// @brief The units that contains an unit that can be get by key.
            typedef std::unordered_map<
                Solar::Types::Basic::String,
                Solar::Core::Graphics::Unit*
            > UnitTable;
            
            /// @brief Contains the units:
            struct Units
            {
                /// @brief All the units present:
                Solar::Core::Graphics::UnitTable units;

                /// @brief The main unit, this is for an fast access of the main unit.
                Solar::Core::Graphics::Unit* main;
            };

            Solar::Core::Graphics::Units UnitsNew();
            void UnitsDestroy(Solar::Core::Graphics::Units* units);
            void UnitsInit(Solar::Core::Graphics::Units* units);
            Solar::Core::Graphics::Unit* UnitsCreateMainUnit(Solar::Core::Graphics::Units* units, const Solar::Types::Basic::U8 mode);
            Solar::Core::Graphics::Unit* UnitsCreateUnit(Solar::Core::Graphics::Units* units, const Solar::Types::Basic::String& key, const Solar::Types::Basic::U8 mode);
            Solar::Core::Graphics::Unit* UnitsGetMainUnit(Solar::Core::Graphics::Units* units);
            Solar::Core::Graphics::Unit* UnitsGetUnit(Solar::Core::Graphics::Units* units, const Solar::Types::Basic::String& key);
        };
    };
};

#endif