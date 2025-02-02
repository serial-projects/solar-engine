#include "Progator/Objects/Buffers/Uniform.hpp"

Progator::Objects::Buffers::Uniform* Progator::Objects::Buffers::UniformNew()
{
    Progator::Objects::Buffers::Uniform* uniform =
        new Progator::Objects::Buffers::Uniform;
    return uniform;
}

void Progator::Objects::Buffers::UniformDestroy(
    Progator::Objects::Buffers::Uniform* uniform,
    Progator::Base::Renderer* renderer
)
{
    uniform->pointers->uniform_buffer_object_destroy(uniform->backend, renderer->backend);
    delete uniform;
}

void Progator::Objects::Buffers::UniformInit(
    Progator::Objects::Buffers::Uniform* uniform,
    Progator::Base::Pointers* pointers,
    Progator::Base::Renderer* renderer,
    Logica::Control::Validator* validator
)
{
    uniform->pointers = pointers;
    uniform->validator = validator;

    uniform->backend = uniform->pointers->uniform_buffer_object_new();
    uniform->pointers->uniform_buffer_object_init(uniform->backend, renderer->backend, validator);
    
    /* DONE: */
}

void Progator::Objects::Buffers::UniformAttachShader(
    Progator::Objects::Buffers::Uniform* uniform,
    Progator::Base::Renderer* renderer,
    Progator::Objects::Shader* shader,
    const Progator::Types::Specifics::UBO::Property property
)
{
    uniform->pointers->uniform_buffer_object_attach_shader(
        uniform->backend,
        renderer->backend,
        shader->backend,
        property
    );
}

void Progator::Objects::Buffers::UniformSetData(
    Progator::Objects::Buffers::Uniform* uniform,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Specifics::UBO::Property property,
    void* data,
    Progator::Types::Basic::U64 size
)
{
    uniform->pointers->uniform_buffer_object_set_data(
        uniform->backend,
        renderer->backend,
        property,
        data,
        size
    );
}