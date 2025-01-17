#ifndef FeraBackendsOBJInterpreterOpcodes_hpp
#define FeraBackendsOBJInterpreterOpcodes_hpp

#include "Fera/Backends/OBJ/Interpreter/Instance.hpp"

/* NOTE: include all the opcodes: */
#include "Fera/Backends/OBJ/Interpreter/Opcodes/CaptainSol.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes/V.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes/VT.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes/VN.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes/S.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes/O.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes/G.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes/F.hpp"

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            namespace Interpreter 
            {
                typedef void(*OpcodeFunction)(Fera::Backends::OBJ::Interpreter::Instance* instance);
                /// @brief contains all the opcodes present on the OBJ file, this is a table to the
                /// reason to be fast to add more opcodes on later versions like bezier for example
                /// so, just keep a table.
                const std::unordered_map<
                    Fera::Types::String,
                    Fera::Backends::OBJ::Interpreter::OpcodeFunction
                > OpcodeTable =
                {
                    {"CaptainSol",  Fera::Backends::OBJ::Interpreter::Opcodes::CaptainSol},
                    {"v",           Fera::Backends::OBJ::Interpreter::Opcodes::V},
                    {"vt",          Fera::Backends::OBJ::Interpreter::Opcodes::VT},
                    {"vn",          Fera::Backends::OBJ::Interpreter::Opcodes::VN},
                    {"s",           Fera::Backends::OBJ::Interpreter::Opcodes::S},
                    {"g",           Fera::Backends::OBJ::Interpreter::Opcodes::G},
                    {"o",           Fera::Backends::OBJ::Interpreter::Opcodes::O},
                    {"f",           Fera::Backends::OBJ::Interpreter::Opcodes::F}
                };
                void InstancePerformOpcode(Fera::Backends::OBJ::Interpreter::Instance* instance, const Fera::Types::String& opcode);
            };
        };
    };
};

#endif