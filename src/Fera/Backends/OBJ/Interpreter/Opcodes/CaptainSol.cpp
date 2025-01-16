#include "Fera/Backends/OBJ/Interpreter/Opcodes/CaptainSol.hpp"

/*
 * For debugging reasons, use "CaptainSol" to show some information about the OBJ interpreter.
 */

#include <iostream>

inline static Fera::Types::String FeraBackendsOBJInterpreterOpcodesCaptainSolShowList(
    Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector& vec
)
{
    Fera::Types::String buffer = "[";
    for(Fera::Types::U8 index=0; index < vec.size() && index < UINT8_MAX; index++)
        buffer = buffer + std::to_string(vec.at(index)) + (index < vec.size() - 1 ? ", " : "]");
    return buffer;
}

void Fera::Backends::OBJ::Interpreter::Opcodes::CaptainSol(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    /* SHOW some information + V information. */
    std::cout
        << __PRETTY_FUNCTION__
        << ": current_group = "
        << instance->current_group
        << " / current_object = "
        << instance->current_object
        << "\n"
        << __PRETTY_FUNCTION__
        << ": instance->V (size) = "
        << instance->current_V.size()
        << "\n";
    
    /* SHOW: V, VT & VN */
    for(Fera::Types::U8 index=0; index < instance->current_V.size() && index < UINT8_MAX; ++index)
        std::cout
            << __PRETTY_FUNCTION__
            << ":\t["
            << (int)index
            << "] = "
            << FeraBackendsOBJInterpreterOpcodesCaptainSolShowList(instance->current_V.at(index))
            << "\n";
    
    std::cout
        << __PRETTY_FUNCTION__
        << ": instance->VT (size) = "
        << instance->current_VT.size()
        << "\n";
    for(Fera::Types::U8 index=0; index < instance->current_VT.size() && index < UINT8_MAX; ++index)
        std::cout
            << __PRETTY_FUNCTION__
            << ":\t["
            << (int)index
            << "] = "
            << FeraBackendsOBJInterpreterOpcodesCaptainSolShowList(instance->current_VT.at(index))
            << "\n";

    std::cout
        << __PRETTY_FUNCTION__
        << ": instance->VN (size) = "
        << instance->current_VN.size()
        << "\n";    
    for(Fera::Types::U8 index=0; index < instance->current_VN.size() && index < UINT8_MAX; ++index)
        std::cout
            << __PRETTY_FUNCTION__
            << ":\t["
            << (int)index
            << "] = "
            << FeraBackendsOBJInterpreterOpcodesCaptainSolShowList(instance->current_VN.at(index))
            << "\n";
    
    /* SHOW the working object: */
    std::cout
        << __PRETTY_FUNCTION__
        << ": instance->working_object (size) = "
        << instance->working_object.size()
        << "\n";
    for(
        Fera::Types::U8 index=0;
        (index<instance->working_object.size() && index < UINT8_MAX);
        ++index
    )
        std::cout
            << __PRETTY_FUNCTION__
            << ":\t["
            << (int)index
            << "]: "
            << instance->working_object.at(index)
            << "\n";
    
    /* Show the objects being shown: */
}