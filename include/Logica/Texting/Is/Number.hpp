#ifndef LogicaTextingIsNumber_hpp
#define LogicaTextingIsNumber_hpp

#include "Logica/Types.hpp"

namespace Logica
{
    namespace Texting
    {
        namespace Is
        {
            Logica::Types::Basic::Result Number(
                const Logica::Types::Basic::String& token,
                const Logica::Types::Basic::Boolean accept_negatives
            );
        };
    };
};

#endif