#ifndef ProgatorTypesSpecificsUBO_hpp
#define ProgatorTypesSpecificsUBO_hpp

#include "Progator/Types/Basic.hpp"

namespace Progator
{
    namespace Types
    {
        namespace Specifics
        {
            namespace UBO
            {
                struct Property
                {
                    Progator::Types::Basic::CH8* key;
                    Progator::Types::Basic::U8 slot;
                };
            };
        };
    };
};

#endif