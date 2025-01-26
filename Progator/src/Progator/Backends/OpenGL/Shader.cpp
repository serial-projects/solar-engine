#include "Progator/Backends/OpenGL/Shader.hpp"

#include "Progator/Config.hpp"
#include "Progator/Validator.hpp"

#define PROGATOR_SHADER_VERTEX_SLOT         0b10000000
#define PROGATOR_SHADER_FRAGMENT_SLOT       0b01000000
#define PROGATOR_SHADER_GEOMETRY_SLOT       0b00100000
#define PROGATOR_SHADER_PROGRAM_SLOT        0b00000001
#define PROGATOR_SHADER_EMPTY_SLOT          0b00000000

Progator::Backends::OpenGL::Shader *Progator::Backends::OpenGL::ShaderNew()
{
    Progator::Backends::OpenGL::Shader* shader = new Progator::Backends::OpenGL::Shader;
    return shader;
}

void Progator::Backends::OpenGL::ShaderDestroy(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer
)
{
    /* for each slot element, check if it is used.*/
    if(shader->slots & PROGATOR_SHADER_VERTEX_SLOT)     glDeleteShader(shader->vertex);
    if(shader->slots & PROGATOR_SHADER_FRAGMENT_SLOT)   glDeleteShader(shader->fragment);
    if(shader->slots & PROGATOR_SHADER_GEOMETRY_SLOT)   glDeleteShader(shader->geometry);
    if(shader->slots & PROGATOR_SHADER_PROGRAM_SLOT)    glDeleteProgram(shader->program);
    
    /* done? */
    delete shader;
}

void Progator::Backends::OpenGL::ShaderInit(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer,
    Logica::Control::Validator *validator
)
{
    shader->slots = PROGATOR_SHADER_EMPTY_SLOT;
    shader->validator = validator;
    /* NOTE: since everything is not initialized YET, do not initialize vertex, fragment and 
     * geometry shader slots. */
}

/* Function Factory: ShaderSet(any)Code */
static inline void __ProgatorBackendsOpenGLShaderSetCode(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Types::AnyShader* shader_target,
    GLenum shader_target_type,
    const Progator::Types::Basic::U8 shader_slot_mask,
    const Progator::Types::Basic::CH8* code,
    const Progator::Types::Basic::U8 validator_error_code,
    const Progator::Types::Basic::CH8* validator_error_message
)
{
    *shader_target = glCreateShader(shader_target_type);
    shader->slots ^= shader_slot_mask;

    glShaderSource(*shader_target, 1, (const char**)&code, NULL);
    glCompileShader(*shader_target);

    Progator::Types::Basic::I32 success;
    Progator::Types::Basic::CH8 buffer[PROGATOR_BACKENDS_OPENGL_SHADER_LOGSIZE];
    glGetShaderiv(*shader_target, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(
            *shader_target,
            PROGATOR_BACKENDS_OPENGL_SHADER_LOGSIZE,
            NULL,
            (GLchar*)&buffer
        );
        shader->validator->SetError(
            validator_error_code,
            validator_error_message,
            buffer
        );
    }
}

void Progator::Backends::OpenGL::ShaderSetVertexCode(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer,
    const Progator::Types::Basic::CH8* code
)
{
    /* use the function factory: */
    __ProgatorBackendsOpenGLShaderSetCode(
        shader,
        &shader->vertex,
        GL_VERTEX_SHADER,
        PROGATOR_SHADER_VERTEX_SLOT,
        code,
        Progator::ValidatorCodes::FailedCompileVertexShader,
        "Failed to compile vertex shader due: %s"
    );
}

void Progator::Backends::OpenGL::ShaderSetFragmentCode(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer,
    const Progator::Types::Basic::CH8* code
)
{
    __ProgatorBackendsOpenGLShaderSetCode(
        shader,
        &shader->fragment,
        GL_FRAGMENT_SHADER,
        PROGATOR_SHADER_FRAGMENT_SLOT,
        code,
        Progator::ValidatorCodes::FailedCompileFragmentShader,
        "Failed to compile fragment shader due: %s"
    );
}

void Progator::Backends::OpenGL::ShaderSetGeometryCode(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer,
    const Progator::Types::Basic::CH8* code
)
{
    __ProgatorBackendsOpenGLShaderSetCode(
        shader,
        &shader->geometry,
        GL_GEOMETRY_SHADER,
        PROGATOR_SHADER_GEOMETRY_SLOT,
        code,
        Progator::ValidatorCodes::FailedCompileGeometryShader,
        "Failed to compile geometry shader due: %s"
    );
}

void Progator::Backends::OpenGL::ShaderLink(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer
)
{
    shader->program = glCreateProgram();
    shader->slots ^= PROGATOR_SHADER_PROGRAM_SLOT;

    /* Go though all the slots and perform linking: */
    if(shader->slots & PROGATOR_SHADER_VERTEX_SLOT)
        glAttachShader(shader->program, shader->vertex);

    if(shader->slots & PROGATOR_SHADER_FRAGMENT_SLOT)
        glAttachShader(shader->program, shader->fragment);

    if(shader->slots & PROGATOR_SHADER_GEOMETRY_SLOT)
        glAttachShader(shader->program, shader->geometry);
}

void Progator::Backends::OpenGL::ShaderCompile(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer
)
{
    glLinkProgram(shader->program);
    Progator::Types::Basic::I32 success;
    Progator::Types::Basic::CH8 buffer[PROGATOR_BACKENDS_OPENGL_SHADER_LOGSIZE];
    glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(
            shader->program,
            PROGATOR_BACKENDS_OPENGL_SHADER_LOGSIZE,
            NULL,
            (GLchar*)&buffer
        );
        shader->validator->SetError(
            Progator::ValidatorCodes::FailedLinkShaders,
            "Failed to link shaders due: %s",
            buffer
        );
    }
}

#define PERFORM_CLEANUP(slot_mask,target_shader)                                                    \
    if(shader->slots & slot_mask) glDeleteShader(target_shader);                                    \
    shader->slots ^= slot_mask;

void Progator::Backends::OpenGL::ShaderClean(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer
)
{
    PERFORM_CLEANUP(PROGATOR_SHADER_VERTEX_SLOT, shader->vertex);
    PERFORM_CLEANUP(PROGATOR_SHADER_FRAGMENT_SLOT, shader->fragment);
    PERFORM_CLEANUP(PROGATOR_SHADER_GEOMETRY_SLOT, shader->geometry);
}

void Progator::Backends::OpenGL::ShaderUse(
    Progator::Backends::OpenGL::Shader *shader,
    Progator::Backends::OpenGL::Renderer *renderer)
{
    glUseProgram(shader->program);
}

/* Here begins the Set Uniform Function Factory: */
#define OPENGL_UNIFORM_NO_LOCATION_FOUND                -1
#define GenericSetUniformFunction(half_type, type, callback)                                        \
void Progator::Backends::OpenGL::ShaderSetUniform##half_type(                                       \
    Progator::Backends::OpenGL::Shader* shader,                                                     \
    Progator::Backends::OpenGL::Renderer* renderer,                                                 \
    const Progator::Types::Basic::CH8* key,                                                               \
    type value                                                                                      \
)                                                                                                   \
{                                                                                                   \
    const Progator::Types::Basic::I32 uniform_location = glGetUniformLocation(shader->program, key);\
    if(uniform_location != OPENGL_UNIFORM_NO_LOCATION_FOUND) callback                               \
}

GenericSetUniformFunction(
    Matrix44,
    const Progator::Types::GLM::Matrix44,
    { glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value)); }
);

GenericSetUniformFunction(
    Matrix33,
    const Progator::Types::GLM::Matrix33,
    { glUniformMatrix3fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value)); }
);

GenericSetUniformFunction(
    Vector4,
    const Progator::Types::GLM::Vector4,
    { glUniform4fv(uniform_location, 1, glm::value_ptr(value)); }
);

GenericSetUniformFunction(
    Vector3,
    const Progator::Types::GLM::Vector3,
    { glUniform3fv(uniform_location, 1, glm::value_ptr(value)); }
);

GenericSetUniformFunction(
    I32,
    const Progator::Types::Basic::I32,
    { glUniform1i(uniform_location, value); }
);

GenericSetUniformFunction(
    U32,
    const Progator::Types::Basic::U32,
    { glUniform1ui(uniform_location, value); }
);

GenericSetUniformFunction(
    F32,
    const Progator::Types::Basic::F32,
    { glUniform1f(uniform_location, value); }
);