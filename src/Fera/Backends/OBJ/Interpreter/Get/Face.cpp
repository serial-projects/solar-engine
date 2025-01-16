#include "Fera/Backends/OBJ/Interpreter/Get/Face.hpp"
#include "Logica/Logica.hpp"

Fera::Backends::OBJ::Interpreter::Get::Indexes Fera::Backends::OBJ::Interpreter::Get::Faces(
    Fera::Backends::OBJ::Interpreter::Instance* instance,
    Fera::Types::String& token
)
{
    Fera::Backends::OBJ::Interpreter::Get::Indexes indexes;
    Logica::Data::String::SplitResult faces = 
        Logica::Data::String::Split(token, '/');
    for(Fera::Types::U8 index=0; index < faces.size() && index < UINT8_MAX; ++index)
    {
        Logica::Types::Basic::String face_token = faces.at(index);
        Logica::Types::Basic::Result is_number_valid =
            Logica::Texting::Is::Number(face_token, false);
        if(is_number_valid)
            indexes.push_back(std::stoi(face_token));
        else
        {
            /* DO NOT accept any other type! */
            instance->state = Fera::Backends::OBJ::Interpreter::InstanceStates::Died;
            instance->validator.SetError(
                Fera::Backends::OBJ::Interpreter::InstanceErrors::InvalidFaceIndex,
                "near at line: %d, invalid face index = %s",
                instance->tokenizer.GetCurrentLine(),
                face_token.c_str()
            );
            break;
        }
    }
    return indexes;
}