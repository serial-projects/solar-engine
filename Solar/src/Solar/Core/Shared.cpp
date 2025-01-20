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
    Solar::Core::GraphicsDestroy(&shared->graphics);
    Solar::Core::BasicsDestroy(&shared->basics);
}

void Solar::Core::SharedInit(
    Solar::Core::Shared* shared
)
{
    Solar::Core::GraphicsInit(&shared->graphics);
    Solar::Core::BasicsInit(&shared->basics);
}