#ifndef ProgatorShader_hpp
#define ProgatorShader_hpp

#include "Progator/Types.hpp"
#include "Progator/Validator.hpp"
#include "Progator/Pointers.hpp"

namespace Progator
{
    typedef struct Shader
    {
        void *backend;
        Progator::Pointers* pointers;
        Progator::Validator* validator;
    } Shader;
    Progator::Shader* ShaderNew();
    void ShaderDestroy(Progator::Shader* shader);
    void ShaderInit(Progator::Shader* shader, Progator::Pointers* pointers, Progator::Validator* validator);
    void ShaderLoadVertexCodeFromFile(Progator::Shader* shader, const Progator::Character* path);
    void ShaderLoadFragmentCodeFromFile(Progator::Shader* shader, const Progator::Character* path);
    void ShaderCompile(Progator::Shader* shader);
    void ShaderUse(Progator::Shader* shader);
    void ShaderSUMatrix44(Progator::Shader* shader, const Progator::Character* key, const Progator::Matrix44 value);
    void ShaderSUMatrix33(Progator::Shader* shader, const Progator::Character* key, const Progator::Matrix33 value);
    void ShaderSUMatrix22(Progator::Shader* shader, const Progator::Character* key, const Progator::Matrix22 value);
    void ShaderSUVector4(Progator::Shader* shader, const Progator::Character* key, const Progator::Vector4 value);
    void ShaderSUVector3(Progator::Shader* shader, const Progator::Character* key, const Progator::Vector3 value);
    void ShaderSUVector2(Progator::Shader* shader, const Progator::Character* key, const Progator::Vector2 value);
    void ShaderSUInteger(Progator::Shader* shader, const Progator::Character* key, const Progator::I32 value);
    void ShaderSUUInteger(Progator::Shader* shader, const Progator::Character* key, const Progator::U32 value);
    void ShaderSURGBA84(Progator::Shader* shader, const Progator::Character* key, const Progator::RGBA84 value);
    void ShaderSUDecimal(Progator::Shader* shader, const Progator::Character* key, const Progator::F32 value);
};

#endif