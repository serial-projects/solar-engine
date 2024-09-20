#ifndef ProgatorValidator_hpp
#define ProgatorValidator_hpp 

#include "Progator/Types.hpp"

namespace Progator
{
    typedef struct Validator
    {
        Progator::U8        status;
        Progator::Character log[256];
    } Validator;
    Progator::Validator* ValidatorNew();
    void ValidatorDestroy(Progator::Validator* validator);
};

#endif