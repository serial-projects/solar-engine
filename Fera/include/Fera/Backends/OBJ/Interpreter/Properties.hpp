#ifndef FeraBackendsOBJProperties_hpp
#define FeraBackendsOBJProperties_hpp

#include "Fera/Types.hpp"

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            namespace Interpreter
            {
                /// @brief Since the OBJ Interpreter is a deterministic machine, we need to know some
                /// properties such as V_size, VT_size, those for example, determine how big is the
                /// vector we are looking for on the textures, V x, y, z, w, ...
                struct Properties
                {
                    /// @brief how much V opcode should look for?
                    Fera::Types::U8 V_size;

                    /// @brief how much VT opcode should look for?
                    Fera::Types::U8 VT_size;

                    /// @brief how much VN opcode should look for?
                    Fera::Types::U8 VN_size;

                    /// @brief Amount of faces you want on the polygon.
                    Fera::Types::U8 F_size;
                };
            };
        };
    };
};

#endif