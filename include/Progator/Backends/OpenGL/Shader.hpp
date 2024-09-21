#ifndef ProgatorBackendsOpenGLShader_hpp
#define ProgatorBackendsOpenGLShader_hpp

#include "Progator/Types.hpp"
#include "Progator/Backends/OpenGL/Basics.hpp"
#include "Progator/Validator.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            typedef struct Shader
            {
                Progator::Backends::OpenGL::FragmentShader fragment_shader;
                Progator::Backends::OpenGL::VertexShader vertex_shader;
                Progator::Backends::OpenGL::ShaderProgram program;
                Progator::Validator* validator;
            } Shader;
            Progator::Backends::OpenGL::Shader* ShaderNew();
            void ShaderDestroy(Progator::Backends::OpenGL::Shader* shader);
            void ShaderInit(Progator::Backends::OpenGL::Shader* shader, Progator::Validator* validator);
            void ShaderLoadVertexCodeFromFile(Progator::Backends::OpenGL::Shader* shader, const Progator::Character* path);
            void ShaderLoadFragmentCodeFromFile(Progator::Backends::OpenGL::Shader* shader, const Progator::Character* path);
            void ShaderCompile(Progator::Backends::OpenGL::Shader* shader);
            void ShaderUse(Progator::Backends::OpenGL::Shader* shader);
            void ShaderSUMatrix44(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Matrix44 value);
            void ShaderSUMatrix33(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Matrix33 value);
            void ShaderSUMatrix22(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Matrix22 value);
            void ShaderSUVector4(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Vector4 value);
            void ShaderSUVector3(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Vector3 value);
            void ShaderSUVector2(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Vector2 value);
            void ShaderSUInteger(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::I32 value);
            void ShaderSUUInteger(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::U32 value);
            void ShaderSURGBA84(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::RGBA84 value);
            void ShaderSUDecimal(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::F32 value);
        };
    };
};

#endif