#include "Progator/Validator.hpp"
#include <cstdarg>
#include <cstdio>

Progator::Validator* Progator::ValidatorNew()
{
    Progator::Validator* proto = new Progator::Validator;
    return proto;
}

void Progator::ValidatorDestroy(Progator::Validator* validator)
{
    delete validator;
}

void Progator::ValidatorError(Progator::Validator* validator, const Progator::U8 code, const Progator::Character* format, ...)
{
    /* NOTE: do everything necessary to the buffer: */
    std::va_list args; va_start(args, format);
    std::vsnprintf(validator->log, 256, format, args);
    va_end(args);

    /* set the code and quit: */
    validator->status = code;
}