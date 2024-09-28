#include "Progator/Progator.hpp"

void Progator::Init(Progator::Validator* validator)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Progator::ValidatorError(
            validator,
            Progator::ValidatorCodes::FailedInitializeSDL,
            "Failed to initialize SDL due: %s\n",
            SDL_GetError()
        );
    }
}

void Progator::Quit()
{
    SDL_Quit();
}