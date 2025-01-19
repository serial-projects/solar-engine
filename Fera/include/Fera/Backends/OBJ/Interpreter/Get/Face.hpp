#ifndef FeraBackendsOBJInterpreterGetFace_hpp
#define FeraBackendsOBJInterpreterGetFace_hpp

#include "Fera/Backends/OBJ/Interpreter/Instance.hpp"

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
                    typedef std::vector<Fera::Types::U32> Indexes;
                    Fera::Backends::OBJ::Interpreter::Get::Indexes Faces(
                        Fera::Backends::OBJ::Interpreter::Instance* instance,
                        Fera::Types::String& token
                    );
                };
            };
        };
    };
};

#endif