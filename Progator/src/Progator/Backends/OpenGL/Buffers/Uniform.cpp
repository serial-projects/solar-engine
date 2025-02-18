#include "Progator/Backends/OpenGL/Buffers/Uniform.hpp"
#include "Progator/Config.hpp"

#ifdef PROGATOR_DEBUG
    #include <iostream>
#endif

Progator::Backends::OpenGL::UniformBufferObject* 
Progator::Backends::OpenGL::UniformBufferObjectNew()
{
    Progator::Backends::OpenGL::UniformBufferObject* ubo = 
        new Progator::Backends::OpenGL::UniformBufferObject;
    return ubo;
}

void Progator::Backends::OpenGL::UniformBufferObjectDestroy(
    Progator::Backends::OpenGL::UniformBufferObject* ubo,
    Progator::Backends::OpenGL::Renderer* renderer
)
{
    glDeleteBuffers(1, &ubo->buffer);
    delete ubo;
}

inline static void __ProgatorBackendsOpenGLUniformBufferObjectBindBuffers(
    Progator::Backends::OpenGL::UniformBufferObject* ubo
)
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo->buffer);
}

void Progator::Backends::OpenGL::UniformBufferObjectInit(
    Progator::Backends::OpenGL::UniformBufferObject* ubo,
    Progator::Backends::OpenGL::Renderer* renderer,
    Logica::Control::Validator* validator
)
{
    /* initialize the UBO */
    glGenBuffers(1, &ubo->buffer);
    ubo->validator = validator;
}

void Progator::Backends::OpenGL::UniformBufferObjectAttachShader(
    Progator::Backends::OpenGL::UniformBufferObject* ubo,
    Progator::Backends::OpenGL::Renderer* renderer,
    Progator::Backends::OpenGL::Shader* shader,
    const Progator::Types::Specifics::UBO::Property property
)
{
    /* NOTE: bind it: */
    __ProgatorBackendsOpenGLUniformBufferObjectBindBuffers(ubo);

    /* Attach the shader: */
    GLuint uniform_block_index = glGetUniformBlockIndex(
        shader->program,
        (const GLchar*)property.key
    );
    if(uniform_block_index != GL_INVALID_INDEX)
    {
        /* pass the UBO: */
        glUniformBlockBinding(
            shader->program,
            uniform_block_index,
            property.slot
        );
    }
    else
    {
        /* TODO: on the future, use validator to log an WARNING. */
        #ifdef PROGATOR_DEBUG
            std::cout
                << __PRETTY_FUNCTION__
                << ": Failed to retrive block = "
                << property.slot
                << ", key = "
                << property.key
                << " to UBO!\n";
            std::cout
                << __PRETTY_FUNCTION__
                << ": !! SHADER WILL NOT BE PASSED THE UBO.\n";
        #endif
    }
}

void Progator::Backends::OpenGL::UniformBufferObjectSetData(
    Progator::Backends::OpenGL::UniformBufferObject* ubo,
    Progator::Backends::OpenGL::Renderer* renderer,
    const Progator::Types::Specifics::UBO::Property property,
    void* data,
    Progator::Types::Basic::U64 size
)
{
    /* Bind to buffer the data: */
    __ProgatorBackendsOpenGLUniformBufferObjectBindBuffers(ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);

    /* Set the data to be aligned: */
    glBindBuffer(GL_UNIFORM_BUFFER, property.slot);
    glBindBufferRange(GL_UNIFORM_BUFFER, property.slot, ubo->buffer, 0, size);

    /* Rebind for the SubData parameter: */
    __ProgatorBackendsOpenGLUniformBufferObjectBindBuffers(ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    /* DONE: */
}