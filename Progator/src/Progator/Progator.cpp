#include "Progator/Progator.hpp"
#include "Progator/Validator.hpp"

void Progator::Init(
    Logica::Control::Validator* validator
)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        validator->SetError(
            Progator::ValidatorCodes::FailedInitializeSDL,
            "Failed to initialize SDL: %s",
            SDL_GetError()
        );
}

void Progator::Quit(
    Logica::Control::Validator* validator
)
{
    SDL_Quit();
}