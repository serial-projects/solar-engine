#include "Progator/Shader.hpp"

Progator::Shader* Progator::ShaderNew()
{
    Progator::Shader* proto = new Progator::Shader;
    return proto;
}

void Progator::ShaderDestroy(Progator::Shader* shader)
{
    shader->pointers->shader_destroy(shader->backend);
    delete shader;
}

void Progator::ShaderInit(Progator::Shader* shader, Progator::Pointers* pointers, Progator::Validator* validator)
{
    shader->validator = validator;
    shader->pointers = pointers;
 
    shader->backend = shader->pointers->shader_new();
    if(shader->backend == nullptr)
    {
        Progator::ValidatorError(
            shader->validator,
            Progator::ValidatorCodes::FailedToCreateObject,
            "Failed to create shader object.\n"
        );
    }
    else
    {
        shader->pointers->shader_init(shader->backend, shader->validator);
    }
}

void Progator::ShaderLoadVertexCodeFromFile(Progator::Shader* shader, const Progator::Character* path)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        { shader->pointers->shader_load_vertex_code_from_file(shader->backend, path); }
    );
}

void Progator::ShaderLoadFragmentCodeFromFile(Progator::Shader* shader, const Progator::Character* path)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        { shader->pointers->shader_load_fragment_code_from_file(shader->backend, path); }
    );
}

void Progator::ShaderCompile(Progator::Shader* shader)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        { shader->pointers->shader_compile(shader->backend); }
    );
}

void Progator::ShaderUse(Progator::Shader* shader)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        { shader->pointers->shader_use(shader->backend); }
    );
}

void Progator::ShaderSUMatrix44(Progator::Shader* shader, const Progator::Character* key, const Progator::Matrix44 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_matrix44(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUMatrix33(Progator::Shader* shader, const Progator::Character* key, const Progator::Matrix33 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_matrix33(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUMatrix22(Progator::Shader* shader, const Progator::Character* key, const Progator::Matrix22 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_matrix22(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUVector4(Progator::Shader* shader, const Progator::Character* key, const Progator::Vector4 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_vector4(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUVector3(Progator::Shader* shader, const Progator::Character* key, const Progator::Vector3 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_vector3(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUVector2(Progator::Shader* shader, const Progator::Character* key, const Progator::Vector2 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_vector2(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUInteger(Progator::Shader* shader, const Progator::Character* key, const Progator::I32 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_integer(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUUInteger(Progator::Shader* shader, const Progator::Character* key, const Progator::U32 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_uinteger(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSURGBA84(Progator::Shader* shader, const Progator::Character* key, const Progator::RGBA84 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_rgba84(
                shader->backend,
                key,
                value
            );
        }
    );
}

void Progator::ShaderSUDecimal(Progator::Shader* shader, const Progator::Character* key, const Progator::F32 value)
{
    ProgatorHelperPerformWhenValidated(
        shader->validator,
        {
            shader->pointers->shader_su_decimal(
                shader->backend,
                key,
                value
            );
        }
    );
}