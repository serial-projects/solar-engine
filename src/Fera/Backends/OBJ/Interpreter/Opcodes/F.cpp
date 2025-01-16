#include "Fera/Backends/OBJ/Interpreter/Opcodes/F.hpp"
#include "Fera/Backends/OBJ/Interpreter/Get/Face.hpp"

#define V_LAYOUT    0
#define VT_LAYOUT   1
#define VN_LAYOUT   2

/// @brief Just a function to set on the correct layout the elements!
/// @param instance 
/// @param value 
/// @param layout_index 
static void __FeraBackendsOBJInterpreterOpcodesFGetLayoutAndPushData(
    Fera::Backends::OBJ::Interpreter::Instance *instance,
    const Fera::Types::U32 index,
    const Fera::Types::U8 layout_index
)
{
    Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector current_data;
    switch(layout_index)
    {
        case V_LAYOUT:      current_data = instance->current_V.at (index - 1); break;
        case VT_LAYOUT:     current_data = instance->current_VT.at(index - 1); break;
        case VN_LAYOUT:     current_data = instance->current_VN.at(index - 1); break;
        default:
            /* TODO: do error here. */
            {
                instance->state = Fera::Backends::OBJ::Interpreter::InstanceStates::Died;
                instance->validator.SetError(
                    Fera::Backends::OBJ::Interpreter::InstanceErrors::NotDefinedIndex,
                    "near line %d, invalid layout? (there are only V/VT/VN) allowed!",
                    instance->tokenizer.GetCurrentLine()
                );
                goto something_bad_happened;
            };
            /* remove this lol, this break is not reachable. */
            break;
    };
    for(auto content : current_data)
        instance->working_object.push_back(content);
    something_bad_happened:
    return;
}

/// @brief From the index, do the loop to load the layout.
/// @param instance the instance to work on.
/// @param face the face splitten.
static inline void __FeraBackendsOBJInterpreterOpcodesFLoadFace(
    Fera::Backends::OBJ::Interpreter::Instance *instance,
    Fera::Backends::OBJ::Interpreter::Get::Indexes& face
)
{
    for(
        Fera::Types::U8 layout_index = 0;
        layout_index<face.size() && layout_index < UINT8_MAX;
        ++layout_index
    )
    {
        __FeraBackendsOBJInterpreterOpcodesFGetLayoutAndPushData(
            instance,
            face.at(layout_index),
            layout_index
        );
    }
}

void Fera::Backends::OBJ::Interpreter::Opcodes::F(
    Fera::Backends::OBJ::Interpreter::Instance *instance
)
{
    /* NOTE: */

    for(
        Fera::Types::U8 index = 0;
        (index < instance->properties.F_size && index < UINT8_MAX);
        ++index
    )
    {
        Logica::Types::Basic::String current_face_token = instance->tokenizer.GetToken(false);
        
        /* TODO: check for EOF here. */
        Fera::Backends::OBJ::Interpreter::Get::Indexes indexes =
            Fera::Backends::OBJ::Interpreter::Get::Faces(instance, current_face_token);
        if(instance->state != Fera::Backends::OBJ::Interpreter::InstanceStates::Running)
            break;
        
        /* advance for the indexing: */
        __FeraBackendsOBJInterpreterOpcodesFLoadFace(instance, indexes);
    }
}