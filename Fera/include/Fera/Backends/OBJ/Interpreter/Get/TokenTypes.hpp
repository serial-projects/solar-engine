#ifndef FeraBackendsOBJInterpreterGetTokenTypes_hpp
#define FeraBackendsOBJInterpreterGetTokenTypes_hpp

#include "Fera/Types.hpp"

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            namespace Interpreter 
            {
                namespace Get
                {
                    namespace TokenTypes
                    {
                        enum TokenTypes
                        {
                            Nothing = 0,
                            Number,
                            Decimal,
                            String,
                            Unknown = UINT8_MAX
                        };
                    };
                    Fera::Types::U8 TokenType(Fera::Types::String& token);
                };
            };
        };
    };
};

#endif