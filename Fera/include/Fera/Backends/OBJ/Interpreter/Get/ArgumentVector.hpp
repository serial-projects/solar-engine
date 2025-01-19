#ifndef FeraBackendsOBJInterpreterGetArgumentVector_hpp
#define FeraBackendsOBJInterpreterGetArgumentVector_hpp

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
                    /// @brief Get from the instance the vectors already (this is very useful since
                    /// V, VT and VN opcodes all do the same).
                    /// @param instance the working instance.
                    /// @param v_size the size of the vector (see Properties)
                    /// @return the argument vector.
                    Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector ArgumentVector(
                        Fera::Backends::OBJ::Interpreter::Instance* instance,
                        const Fera::Types::U8 v_size
                    );
                };
            };
        };
    };
};

#endif