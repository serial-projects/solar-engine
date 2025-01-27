#ifndef Progator_hpp
#define Progator_hpp

#include "Progator/Types.hpp"
#include "Progator/Base.hpp"
#include "Progator/Validator.hpp"
#include "Progator/Objects.hpp"

namespace Progator
{
    void Init(Logica::Control::Validator* validator);
    void Quit(Logica::Control::Validator* validator);
};

#endif