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
    Solar::Core::Provider::WarehouseDestroy(&shared->warehouse);
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

    /* Init the warehouse: */
    shared->warehouse = Solar::Core::Provider::WarehouseNew();
    Solar::Core::Provider::WarehouseInit(&shared->warehouse, &shared->units);
    Solar::Core::Provider::WarehouseAddPath(&shared->warehouse, "root", "./Game/");

    /* Init the basics: */
    Solar::Core::BasicsInit(&shared->basics);
}