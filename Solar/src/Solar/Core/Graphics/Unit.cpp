#include "Solar/Core/Graphics/Unit.hpp"

Solar::Core::Graphics::Unit* Solar::Core::Graphics::UnitNew()
{
    Solar::Core::Graphics::Unit* unit = new Solar::Core::Graphics::Unit;
    return unit;
}

void Solar::Core::Graphics::UnitDestroy(
    Solar::Core::Graphics::Unit* unit
)
{
    Progator::Base::RendererDestroy(unit->renderer);
    Progator::Base::WindowDestroy(unit->window);
    Progator::Base::PointersDestroy(&unit->pointers);
    delete unit;
}

void Solar::Core::Graphics::UnitInit(
    Solar::Core::Graphics::Unit* unit,
    const Solar::Types::Basic::U8 mode
)
{
    unit->validator = Logica::Control::Validator();
    
    unit->pointers = Progator::Base::PointersNew();
    Progator::Base::PointersInit(&unit->pointers);
    switch(mode)
    {
        case Progator::Base::PointersBackend::OpenGL:
            Progator::Base::PointersSetOpenGLMode(&unit->pointers);
            break;
        default:
            std::abort();
            break;
    };

    /* keep going: */
    unit->window = Progator::Base::WindowNew();
    Progator::Base::WindowInit(unit->window, &unit->pointers, &unit->validator);
    
    unit->renderer = Progator::Base::RendererNew();
    Progator::Base::RendererInit(unit->renderer, unit->window, &unit->pointers, &unit->validator);
    Progator::Base::RendererSetViewport(
        unit->renderer, {
            .width  = unit->window->geometry.width,
            .height = unit->window->geometry.height,
            .x      = 0,
            .y      = 0
        }
    );
}