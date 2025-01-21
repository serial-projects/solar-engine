#include "Solar/Core/Graphics/Units.hpp"
#include <iostream>

Solar::Core::Graphics::Units Solar::Core::Graphics::UnitsNew()
{
    Solar::Core::Graphics::Units graphics;
    return graphics;
}

void Solar::Core::Graphics::UnitsDestroy(
    Solar::Core::Graphics::Units* graphics
)
{
    /* delete all the units: */
    for(auto& content : graphics->units)
        Solar::Core::Graphics::UnitDestroy(content.second);
    graphics->main = nullptr;
}

void Solar::Core::Graphics::UnitsInit(
    Solar::Core::Graphics::Units* graphics
)
{
    graphics->units = Solar::Core::Graphics::UnitTable();
    graphics->main = nullptr;
}

Solar::Core::Graphics::Unit* Solar::Core::Graphics::UnitsCreateMainUnit(
    Solar::Core::Graphics::Units* graphics,
    const Solar::Types::Basic::U8 mode
)
{
    graphics->main = Solar::Core::Graphics::UnitsCreateUnit(graphics, "main", mode);
    return graphics->main;
}

Solar::Core::Graphics::Unit* Solar::Core::Graphics::UnitsCreateUnit(
    Solar::Core::Graphics::Units* graphics,
    const Solar::Types::Basic::String& key,
    const Solar::Types::Basic::U8 mode
)
{
    Solar::Core::Graphics::Unit* unit = Solar::Core::Graphics::UnitNew();
    Solar::Core::Graphics::UnitInit(unit, mode);
    graphics->units.insert({ key, unit });
    return unit;
}

Solar::Core::Graphics::Unit* Solar::Core::Graphics::UnitsGetMainUnit(
    Solar::Core::Graphics::Units* graphics
)
{
    return graphics->main;
}

Solar::Core::Graphics::Unit* Solar::Core::Graphics::UnitsGetUnit(
    Solar::Core::Graphics::Units* graphics,
    const Solar::Types::Basic::String& key
)
{
    Solar::Core::Graphics::Unit* unit = nullptr;
    if(graphics->units.find(key) == graphics->units.end())
        unit = graphics->units.at(key);
    return unit;
}