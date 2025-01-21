#include "Solar/Core/Shared.hpp"

Solar::Core::Shared SharedNew()
{
    Solar::Core::Shared shared;
    return shared;
}

void Solar::Core::SharedDestroy(
    Solar::Core::Shared* shared
)
{
    Solar::Core::Graphics::UnitsDestroy(&shared->units);
    Solar::Core::BasicsDestroy(&shared->basics);
    
    Progator::Quit(&shared->validator);
}

void Solar::Core::SharedInit(
    Solar::Core::Shared* shared
)
{
    Progator::Init(&shared->validator);

    /* Initialize the Units (aka. the graphics): */
    Solar::Core::Graphics::UnitsInit(&shared->units);
    Solar::Core::Graphics::UnitsCreateMainUnit(
        &shared->units,
        Progator::Base::PointersBackend::OpenGL
    );
    Solar::Core::BasicsInit(&shared->basics);
}