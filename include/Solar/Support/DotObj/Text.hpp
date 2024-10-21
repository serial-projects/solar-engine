#ifndef SolarSupportDotObjText_hpp
#define SolarSupportDotObjText_hpp

/*
 * NOTE: on Solar Engine, there is no groups or either an reason for it anyway, groups could make
 * sense if the Solar Engine had the objective of using the OBJ file for true rendering which is
 * not the objective of the engine itself or not now, for customize the appearance, lightning and
 * other features, see the model customization features during on the '.scmo' files.
 * 
 * BUT, support object names:
 */

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Support
    {
        namespace DotObj
        {
            /* Basic Validator: */
            enum ValidatorStates
            {
                Ok              = 0,
                Failed
            };

            typedef struct Validator
            {
                Solar::String log;
                Solar::Support::DotObj::ValidatorStates state;
            } Validator;
            Solar::Support::DotObj::Validator* ValidatorNew();
            void ValidatorDestroy(Solar::Support::DotObj::Validator* validator);

            /* data: */
            typedef std::vector<Solar::F32> ObjectData;
            Solar::Support::DotObj::ObjectData* ObjectDataNew();
            void ObjectDataDestroy(Solar::Support::DotObj::ObjectData* object_data);

            typedef std::unordered_map<Solar::String, Solar::Support::DotObj::ObjectData*> Objects;
            void ObjectsDestroy(Solar::Support::DotObj::Objects* objects);

            /* interpreter: */
            enum InterpreterStates
            {
                Running     = 0,
                Finished,
                Died
            };

            typedef struct Interpreter
            {
                /* Validator: */
                Solar::Support::DotObj::Validator* validator;

                /* buffer: */
                Solar::String *buffer;
                Solar::U64 buffer_index;
                Solar::U64 buffer_length;
                Solar::U32 line_counter;

                /* buffers: */
                std::vector < Solar::Vector3 > current_vertices;
                std::vector < Solar::Vector2 > current_texmaps;
                std::vector < Solar::Vector3 > current_normals;
                
                /* object construction: */
                Solar::String current_object;
                Solar::Support::DotObj::Objects objects;
                Solar::Support::DotObj::InterpreterStates state;
            } Interpreter;
            Solar::Support::DotObj::Interpreter* InterpreterNew();
            void InterpreterDestroy(Solar::Support::DotObj::Interpreter* interpreter);
            void InterpreterInit(Solar::Support::DotObj::Interpreter* interpreter, Solar::Support::DotObj::Validator* validator, Solar::String* buffer);
            void InterpreterStep(Solar::Support::DotObj::Interpreter* interpreter);
        };
    };
};

#endif