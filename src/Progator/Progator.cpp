#include "Progator/Progator.hpp"

void Progator::Init(Progator::Validator* validator)
{
    SDL_Init(SDL_INIT_EVERYTHING);
}

void Progator::Quit()
{
    SDL_Quit();
}