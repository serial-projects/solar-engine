#ifndef ProgatorTypesTuningEngine_hpp
#define ProgatorTypesTuningEngine_hpp

#include "Progator/Types/Basic.hpp"

namespace Progator
{
    namespace Types
    {
        namespace Tuning
        {
            namespace Engine
            {
                /// @brief this contains the stubs for the VkApplicationInfo.
                struct Properties
                {
                    Progator::Types::Basic::CH8*    application_name;
                    Progator::Types::Basic::U32     application_version;
                    Progator::Types::Basic::CH8*    engine_name;
                    Progator::Types::Basic::U32     engine_version;                
                };
            };
        };
    };
};

#endif