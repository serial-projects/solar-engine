#ifndef ProgatorBackendsOpenGLShader_hpp
#define ProgatorBackendsOpenGLShader_hpp

#include "Progator/Types.hpp"
#include "Progator/Backends/OpenGL/Types.hpp"
#include "Progator/Backends/OpenGL/Renderer.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            struct Shader
            {
                /* Validator & Shader slots: */
                Logica::Control::Validator* validator;
                Progator::Types::Basic::U8 slots;
                
                /* Vertex, Fragment, Geometry: Those are the only compatible shaders: */
                Progator::Backends::OpenGL::Types::VertexShader vertex;
                Progator::Backends::OpenGL::Types::FragmentShader fragment;
                Progator::Backends::OpenGL::Types::GeometryShader geometry;

                /* The result of the v/f/g? shaders: */
                Progator::Backends::OpenGL::Types::ShaderProgram program;
            };
            
            Progator::Backends::OpenGL::Shader* ShaderNew();
            
            void ShaderDestroy(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer);
            
            void ShaderInit(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, Logica::Control::Validator* validator);
            
            void ShaderSetVertexCode(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* code);
            void ShaderSetFragmentCode(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* code);
            void ShaderSetGeometryCode(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* code);
            
            
            void ShaderLink(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer);
            void ShaderCompile(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer);
            void ShaderClean(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer);

            void ShaderUse(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer);

            void ShaderSetUniformMatrix44(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Matrix44 value);
            void ShaderSetUniformMatrix33(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Matrix33 value);
            void ShaderSetUniformVector4(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Vector4 value);
            void ShaderSetUniformVector3(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Vector3 value);
            void ShaderSetUniformI32(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::I32 value);
            void ShaderSetUniformU32(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::U32 value);
            void ShaderSetUniformF32(Progator::Backends::OpenGL::Shader* shader, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::F32 value);
        };
    };
};

#endif