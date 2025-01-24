#include "Solar/Core/Shared.hpp"

// TODO: for debug only!
#include <iostream>

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

    /* Init the basics: */
    Solar::Core::BasicsInit(&shared->basics);

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

    /* TODO: this might dirt the system but if the content provider fails, then crash the whole
     * system and generate a global dump! */
    shared->warehouse.validator.SetUserDataForCallback(
        (void*)shared
    );
    shared->warehouse.validator.SetErrorCallback(
        [](Logica::Control::ValidatorValues* validator, void* userdata){
            /* Prepare for the SDL Error: */
            const Solar::Types::Basic::String text = 
                "Fatal: " + validator->buffer;

            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR,
                "Solar Engine (Content Provider, aka. Warehouse)",
                text.c_str(),
                NULL
            );
            
            // NOTE: set the state to 0, this will automatically never run the next frame.
            Solar::Core::Shared* shared_core = (Solar::Core::Shared*)(userdata);
            shared_core->basics.state = 0;
        }
    );
}