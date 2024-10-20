#include "Solar/Support/DotObj/Text.hpp"
#include <iostream>

/*
 * README:
 * 1-) The DotObj file parser only supports triangulated meshes that contains
 * well defined normals and texture map, there is no flexibility.
 * 
 * 2-) It is not stable enough.
 */

/*
 * Validator:
 */

Solar::Support::DotObj::Validator* Solar::Support::DotObj::ValidatorNew()
{
    Solar::Support::DotObj::Validator* proto = new
        Solar::Support::DotObj::Validator;
    return proto;
}

void Solar::Support::DotObj::ValidatorDestroy(
    Solar::Support::DotObj::Validator* validator
)
{
    delete validator;
}

/*
 * ObjectData:
 */
Solar::Support::DotObj::ObjectData* Solar::Support::DotObj::ObjectDataNew()
{
    Solar::Support::DotObj::ObjectData* proto = new
        Solar::Support::DotObj::ObjectData;
    return proto;
}

void Solar::Support::DotObj::ObjectDataDestroy(
    Solar::Support::DotObj::ObjectData* object_data
)
{
    delete object_data;
}

void Solar::Support::DotObj::ObjectsDestroy(
    Solar::Support::DotObj::Objects* objects
)
{
    for(auto &value : *objects) Solar::Support::DotObj::ObjectDataDestroy(value.second);
}

/* 
 * Interpreter:
 */

/* #define SOLAR_ENABLE_DEBUG */
#ifdef SOLAR_ENABLE_DEBUG
    #define DEBUG(expression) \
        std::cout << __PRETTY_FUNCTION__ << ": " << expression << "\n"
#else
    #define DEBUG(expression)
#endif

static Solar::Character InterpreterEatBuffer(
    Solar::Support::DotObj::Interpreter* interpreter
)
{
    Solar::Character ch = 0;
    if(interpreter->buffer_index <= interpreter->buffer_length)
    {
        ch = interpreter->buffer->at(interpreter->buffer_index);
        interpreter->buffer_index++;
    }
    else
    {
        /* set the character: */
        DEBUG("buffer has finished.");
    }
    return ch;
}

static Solar::String InterpreterGetTrueToken(
    Solar::Support::DotObj::Interpreter* interpreter,
    Solar::Character first_character
)
{
    /* true token is all token that is delimited by ' ' or '\n' or '\t' */
    Solar::String accumulator; accumulator.push_back(first_character);
    for(;;)
    {
        Solar::Character ch = InterpreterEatBuffer(interpreter);
        if((ch == ' ' || ch == '\n' || ch == '\t' || ch == '#' || ch == 0)) 
        {
            if((ch == '\n'))
                interpreter->line_counter++;
            DEBUG("token delimitation found, quitting loop.");
            break;
        }
        else accumulator.push_back(ch);
    }
    DEBUG("token found = " << accumulator);
    return accumulator;
}

static Solar::String InterpreterGetString(
    Solar::Support::DotObj::Interpreter* interpreter,
    const Solar::Character strdel
)
{
    Solar::String accumulator;
    for(;;)
    {
        Solar::Character ch = InterpreterEatBuffer(interpreter);
        if((ch == strdel)) break;
        else
        {
            if(ch == '\n')
                interpreter->line_counter++;
            accumulator.push_back(ch);
        }
    }
    return accumulator;
}

static Solar::String InterpreterGetToken(
    Solar::Support::DotObj::Interpreter* interpreter
)
{
    /* check for first character, there are few possibities that can happen during the file
     * parsing, they are '\' for line breaking but no end and strings... Yes, Solar Engine's 
     * OBJ interpreter supports strings on sections in special.
     */
top:
    Solar::String       token = Solar::String();
    Solar::Character    first_ch = InterpreterEatBuffer(interpreter);
    DEBUG("first character on line: " << first_ch << ", line: " << interpreter->line_counter);
    if((first_ch == '\n'))
    {
        /* keep going to the next character and increment the line counter: */
        if(first_ch == '\n')
            interpreter->line_counter++;
        goto top;
    }
    else if((first_ch == '\t' || first_ch == ' '))
    {
        /* keep going to the next character: */
        goto top;
    }
    else if((first_ch == '"' || first_ch == '\''))
    {
        /* do strings: */
        token = InterpreterGetString(
            interpreter,
            first_ch
        );
    }
    else if((first_ch == '#'))
    {
        /* do comment: */
        DEBUG("comment found, waiting for new line...");
        for(;;)
        {
            Solar::Character ch = InterpreterEatBuffer(interpreter);
            if(ch == '\n')
            {
                DEBUG("found new line at index = " << interpreter->buffer_index - 1);
                interpreter->line_counter++;
                goto top;
            }
        }
    }
    else if((first_ch == 0))
    {
        /* keep going : */
        DEBUG("found buffer end, returning empty string.");
    }
    else
    {
        /* do token: */
        token = InterpreterGetTrueToken(
            interpreter,
            first_ch
        );
    }
    return token;
}

typedef std::vector<Solar::U32> SplitenFaces;
static SplitenFaces SplitFaces(const Solar::String *face_string)
{
    std::vector<Solar::U32> faces;
    Solar::String accumulator;
    for(Solar::U16 index=0; index < face_string->size(); index++)
    {
        Solar::Character ch = face_string->at(index);
        if(ch == '/')
        {
            /* set ZERO since faces on OBJ always start with 1, zero can be our safe zone! */
            if(accumulator.size() <= 0)
                accumulator = "0";
            const Solar::U32 number = std::stoul(accumulator);
            faces.push_back(number);
            accumulator.clear();
        }
        else
        {
            accumulator.push_back(ch);
        }
    }
    if(accumulator.size() > 0)
    {
        const Solar::U32 number = std::stoul(accumulator);
        faces.push_back(number);
    }
    return faces;
}

Solar::Support::DotObj::Interpreter* Solar::Support::DotObj::InterpreterNew()
{
    Solar::Support::DotObj::Interpreter* proto = new
        Solar::Support::DotObj::Interpreter;
    return proto;
}

void Solar::Support::DotObj::InterpreterDestroy(
    Solar::Support::DotObj::Interpreter* interpreter
)
{
    Solar::Support::DotObj::ObjectsDestroy(&interpreter->objects);
    delete interpreter;
}

void Solar::Support::DotObj::InterpreterInit(
    Solar::Support::DotObj::Interpreter* interpreter,
    Solar::Support::DotObj::Validator* validator,
    Solar::String* buffer
)
{
    /* set the buffer parsing: */
    interpreter->buffer         = buffer;
    interpreter->buffer_index   = 0;
    interpreter->buffer_length  = buffer->size() - 1;
    interpreter->state          = Running;

    /* set the validator: */
    interpreter->validator = validator;

    /* set the objects: */
    interpreter->current_object = "main";
    interpreter->objects["main"] = Solar::Support::DotObj::ObjectDataNew();
}

/*
 * Interpreter Step & Opcodes:
 */

#define UNIMPLEMENTED_OPCODE(opcode_name)   \
    std::cerr                               \
        << __PRETTY_FUNCTION__              \
        << ": unimplemented DotObj opcode: "\
        << opcode_name                      \
        << ", skipping!\n"

#define UNSUPPORTED_OPCODE(opcode_name)     \
    std::cerr                               \
        << __PRETTY_FUNCTION__              \
        << ": unsupported DotObj opcode: "  \
        << opcode_name                      \
        << ", skipping!\n"

namespace InterpreterOpcodes
{
    /* mtl functionality: */
    static void mtllib(Solar::Support::DotObj::Interpreter* interpreter)
    {
        UNIMPLEMENTED_OPCODE("mtllib");
        InterpreterGetToken(interpreter);
    }

    static void usemtl(Solar::Support::DotObj::Interpreter* interpreter)
    {
        UNIMPLEMENTED_OPCODE("usemtl");
        InterpreterGetToken(interpreter);
    }
    
    /* shading: */
    static void s(Solar::Support::DotObj::Interpreter* interpreter)
    {
        UNIMPLEMENTED_OPCODE("s");
        InterpreterGetToken(interpreter);
    }
    
    /* vertices and faces: */
    static void v(Solar::Support::DotObj::Interpreter* interpreter)
    {
        const Solar::String XT = InterpreterGetToken(interpreter);
        const Solar::String YT = InterpreterGetToken(interpreter);
        const Solar::String ZT = InterpreterGetToken(interpreter);
        const Solar::F32 X = std::stof(XT);
        const Solar::F32 Y = std::stof(YT);
        const Solar::F32 Z = std::stof(ZT);
        
        DEBUG("v(" << X << ", " << Y << ", " << Z << ")");

        /* push: */
        Solar::Support::DotObj::ObjectData* current_object_data =
            interpreter->objects[interpreter->current_object];
        interpreter->current_vertices.push_back(Solar::Vector3(X, Y, Z));
    }

    static void vt(Solar::Support::DotObj::Interpreter* interpreter)
    {
        const Solar::String XT = InterpreterGetToken(interpreter);
        const Solar::String YT = InterpreterGetToken(interpreter);
        const Solar::F32 X = std::stof(XT);
        const Solar::F32 Y = std::stof(YT);
        
        DEBUG("vt(" << X << ", " << Y << ")");

        /* push: */
        Solar::Support::DotObj::ObjectData* current_object_data =
            interpreter->objects[interpreter->current_object];
        interpreter->current_texmaps.push_back(Solar::Vector2(X, Y));
    }

    static void vn(Solar::Support::DotObj::Interpreter* interpreter)
    {
        const Solar::String XT = InterpreterGetToken(interpreter);
        const Solar::String YT = InterpreterGetToken(interpreter);
        const Solar::String ZT = InterpreterGetToken(interpreter);
        const Solar::F32 X = std::stof(XT);
        const Solar::F32 Y = std::stof(YT);
        const Solar::F32 Z = std::stof(ZT);

        DEBUG("vn(" << X << ", " << Y << ", " << Z << ")");
        
        /* push: */
        Solar::Support::DotObj::ObjectData* current_object_data =
            interpreter->objects[interpreter->current_object];
        interpreter->current_normals.push_back(Solar::Vector3(X, Y, Z));
    }

    static void f(Solar::Support::DotObj::Interpreter* interpreter)
    {
        /* f X*/
        const Solar::String XTF = InterpreterGetToken(interpreter);
        const Solar::String YTF = InterpreterGetToken(interpreter);
        const Solar::String ZTF = InterpreterGetToken(interpreter);
        const SplitenFaces XF   = SplitFaces(&XTF);
        const SplitenFaces YF   = SplitFaces(&YTF);
        const SplitenFaces ZF   = SplitFaces(&ZTF);

        /* adquire the current object: */
        Solar::Support::DotObj::ObjectData* current_object_data =
            interpreter->objects[interpreter->current_object];
        
        /* begin mounting the data: */
        
        /* BUG:
         * This won't allow for much flexibility, maybe on the future consider models that doesn't
         * use normals and textures, also, use F that supports QUADS, for now, this f function
         * only supports triangulated meshes.
         */

        const Solar::Vector3 XVE  = interpreter->current_vertices.at(XF[0] - 1);
        const Solar::Vector2 XVT  = XF[1] == 0 ?
            Solar::Vector2(0.0f, 0.0f) : interpreter->current_texmaps.at (XF[1] - 1);
        const Solar::Vector3 XVN  = interpreter->current_normals.at (XF[2] - 1);
        
        const Solar::Vector3 YVE  = interpreter->current_vertices.at(YF[0] - 1);
        const Solar::Vector2 YVT  = YF[1] == 0 ?
            Solar::Vector2(0.0f, 0.0f) : interpreter->current_texmaps.at (YF[1] - 1);
        const Solar::Vector3 YVN  = interpreter->current_normals.at (YF[2] - 1);

        const Solar::Vector3 ZVE  = interpreter->current_vertices.at(ZF[0] - 1);
        const Solar::Vector2 ZVT  = ZF[2] == 0 ?
            Solar::Vector2(0.0f, 0.0f) : interpreter->current_texmaps.at (ZF[1] - 1);
        const Solar::Vector3 ZVN  = interpreter->current_normals.at (ZF[2] - 1);

        #ifdef SOLAR_ENABLE_DEBUG
        std::printf(
            "%s:"
            "f-> (%f, %f, %f)/(%f, %f)/(%f, %f, %f) "
            "(%f, %f, %f)/(%f, %f)/(%f, %f, %f) "
            "(%f, %f, %f)/(%f, %f)/(%f, %f, %f) "
            "\n"
            ,
            __PRETTY_FUNCTION__,
            XVE.x, XVE.y, XVE.z,
            XVT.x, XVT.y,
            XVN.x, XVN.y, XVN.z,
            
            YVE.x, YVE.y, YVE.z,
            YVT.x, YVT.y,
            YVN.x, YVN.y, YVN.z,

            ZVE.x, ZVE.y, ZVE.z,
            ZVT.x, ZVT.y,
            ZVN.x, ZVN.y, ZVN.z
        );
        #endif

        #define VPUSH3(VE)                                              \
            current_object_data->constructed_buffer.push_back(VE.x);    \
            current_object_data->constructed_buffer.push_back(VE.y);    \
            current_object_data->constructed_buffer.push_back(VE.z);
        
        #define VPUSH2(VE)                                              \
            current_object_data->constructed_buffer.push_back(VE.x);    \
            current_object_data->constructed_buffer.push_back(VE.y);

        /* NOTE: push all the data into the buffer: */
        VPUSH3(XVE); VPUSH2(XVT); VPUSH3(XVN);
        VPUSH3(YVE); VPUSH2(YVT); VPUSH3(YVN);
        VPUSH3(ZVE); VPUSH2(ZVT); VPUSH3(ZVN);
    }

    /* group and object: */
    static void g(Solar::Support::DotObj::Interpreter* interpreter)
    {
        const Solar::String ON = InterpreterGetToken(interpreter);
        DEBUG("group = " << ON);
        interpreter->current_object = ON;
        interpreter->objects[interpreter->current_object] =
            Solar::Support::DotObj::ObjectDataNew();
    }
    static void o(Solar::Support::DotObj::Interpreter* interpreter)
    {
        const Solar::String ON = InterpreterGetToken(interpreter);
        DEBUG("object name = " << ON);

        interpreter->current_object = ON;
        interpreter->objects[interpreter->current_object] =
            Solar::Support::DotObj::ObjectDataNew();
    }

    /* table containing all the valid opcodes: */
    typedef void(*Wrapper)(Solar::Support::DotObj::Interpreter* interpreter);
    std::unordered_map<Solar::String, InterpreterOpcodes::Wrapper> Table = {
        {"mtllib",                  InterpreterOpcodes::mtllib},
        {"usemtl",                  InterpreterOpcodes::usemtl},
        {"s",                       InterpreterOpcodes::s},
        {"v",                       InterpreterOpcodes::v},
        {"vt",                      InterpreterOpcodes::vt},
        {"vn",                      InterpreterOpcodes::vn},
        {"f",                       InterpreterOpcodes::f},
        {"g",                       InterpreterOpcodes::g},
        {"o",                       InterpreterOpcodes::o}
    };
};

static void InterpreterPerformOpcode(
    Solar::Support::DotObj::Interpreter* interpreter,
    const Solar::String opcode
)
{
    /* NOTE: to finish the machine, an opcode of size 0 must be set, during the parsing, it is
     * impossible for an opcode with that in OBJ to be present.
     */
    if(opcode.size() > 0)
    {
        DEBUG("performing opcode = " << opcode);
        if(InterpreterOpcodes::Table.find(opcode) != InterpreterOpcodes::Table.end())
            InterpreterOpcodes::Table.at(opcode)(interpreter);
        else
        {
            interpreter->validator->log = (
                "line: "
                + std::to_string(interpreter->line_counter)
                + ", invalid opcodes: "
                + opcode
            );
            interpreter->validator->state = Solar::Support::DotObj::ValidatorStates::Failed;
            interpreter->state = Solar::Support::DotObj::InterpreterStates::Died;
        }
    }
    else
    {
        DEBUG("buffer is over, ending the parsing.");
        interpreter->state = Solar::Support::DotObj::InterpreterStates::Finished;
    }
}

void Solar::Support::DotObj::InterpreterStep(
    Solar::Support::DotObj::Interpreter* interpreter
)
{
    if(interpreter->buffer_index >= interpreter->buffer_length)
        interpreter->state = Finished;

    /* keep going if the machine is running: */
    if(interpreter->state == Running)
    {
        const Solar::String current_opcode = InterpreterGetToken(interpreter);
        InterpreterPerformOpcode(interpreter, current_opcode);
    }
}

/* NOTE: undefine this since we are not needing it anymore. */
#undef DEBUG