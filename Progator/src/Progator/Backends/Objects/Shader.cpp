#include "Progator/Objects/Shader.hpp"

Progator::Objects::Shader* Progator::Objects::ShaderNew()
{
    Progator::Objects::Shader* shader = new Progator::Objects::Shader;
    return shader;
}

void Progator::Objects::ShaderDestroy(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer
)
{
    shader->pointers->shader_destroy(
        shader->backend,
        renderer->backend
    );
    delete shader;
}

void Progator::Objects::ShaderInit(
    Progator::Objects::Shader* shader,
    Progator::Base::Pointers* pointers,
    Progator::Base::Renderer* renderer,
    Logica::Control::Validator* validator
)
{
    shader->pointers = pointers;
    shader->validator = validator;
    
    /* init the backend: */
    shader->backend = shader->pointers->shader_new();
    shader->pointers->shader_init(shader->backend, renderer->backend, shader->validator);
}

void Progator::Objects::ShaderSetVertexCode(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* code
)
{
    shader->pointers->shader_set_vertex_code(shader->backend, renderer->backend, code);
}

void Progator::Objects::ShaderSetFragmentCode(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* code
)
{
    shader->pointers->shader_set_fragment_code(shader->backend, renderer->backend, code);
}

void Progator::Objects::ShaderSetGeometryCode(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* code
)
{
    shader->pointers->shader_set_geometry_code(shader->backend, renderer->backend, code);
}

void Progator::Objects::ShaderLink(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer
)
{
    shader->pointers->shader_link(shader->backend, renderer->backend);
}

void Progator::Objects::ShaderCompile(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer
)
{
    shader->pointers->shader_compile(shader->backend, renderer->backend);
}

void Progator::Objects::ShaderClean(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer
)
{
    shader->pointers->shader_clean(shader->backend, renderer->backend);
}

void Progator::Objects::ShaderUse(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer
)
{
    shader->pointers->shader_use(shader->backend, renderer->backend);
}

void Progator::Objects::ShaderSetUniformMatrix44(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* key,
    const Progator::Types::GLM::Matrix44 value
)
{
    shader->pointers->shader_set_uniform_matrix44(shader->backend, renderer->backend, key, value);
}

void Progator::Objects::ShaderSetUniformMatrix33(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* key,
    const Progator::Types::GLM::Matrix33 value
)
{
    shader->pointers->shader_set_uniform_matrix33(shader->backend, renderer->backend, key, value);
}

void Progator::Objects::ShaderSetUniformVector4(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* key,
    const Progator::Types::GLM::Vector4 value
)
{
    shader->pointers->shader_set_uniform_vector4(shader->backend, renderer->backend, key, value);
}

void Progator::Objects::ShaderSetUniformVector3(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* key,
    const Progator::Types::GLM::Vector3 value
)
{
    shader->pointers->shader_set_uniform_vector3(shader->backend, renderer->backend, key, value);
}

void Progator::Objects::ShaderSetUniformI32(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* key,
    const Progator::Types::Basic::I32 value
)
{
    shader->pointers->shader_set_uniform_i32(shader->backend, renderer->backend, key, value);
}

void Progator::Objects::ShaderSetUniformU32(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* key,
    const Progator::Types::Basic::U32 value
)
{
    shader->pointers->shader_set_uniform_u32(shader->backend, renderer->backend, key, value);
}

void Progator::Objects::ShaderSetUniformF32(
    Progator::Objects::Shader* shader,
    Progator::Base::Renderer* renderer,
    const Progator::Types::Basic::CH8* key,
    const Progator::Types::Basic::F32 value
)
{
    shader->pointers->shader_set_uniform_f32(shader->backend, renderer->backend, key, value);
}