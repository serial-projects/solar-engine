#include "Progator/Validator.hpp"

Progator::Validator* Progator::ValidatorNew()
{
    Progator::Validator* proto = new Progator::Validator;
    return proto;
}

void Progator::ValidatorDestroy(Progator::Validator* validator)
{
    delete validator;
}