#ifndef ProgatorObjectsShader_hpp
#define ProgatorObjectsShader_hpp

#include "Progator/Types.hpp"
#include "Progator/Base/Renderer.hpp"
#include "Progator/Base/Pointers.hpp"

namespace Progator
{
    namespace Objects
    {
        struct Shader
        {
            void* backend;
            Progator::Base::Pointers* pointers;
            Logica::Control::Validator* validator;
        };
        
        Progator::Objects::Shader* ShaderNew();
        
        void ShaderDestroy(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer);
        
        void ShaderInit(Progator::Objects::Shader* shader, Progator::Base::Pointers* pointers, Progator::Base::Renderer* renderer, Logica::Control::Validator* validator);
        
        void ShaderSetVertexCode(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* code);
        void ShaderSetFragmentCode(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* code);
        void ShaderSetGeometryCode(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* code);
        
        
        void ShaderLink(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer);
        void ShaderCompile(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer);
        void ShaderClean(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer);

        void ShaderUse(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer);

        void ShaderSetUniformMatrix44(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Matrix44 value);
        void ShaderSetUniformMatrix33(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Matrix33 value);
        void ShaderSetUniformVector4(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Vector4 value);
        void ShaderSetUniformVector3(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::GLM::Vector3 value);
        void ShaderSetUniformI32(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::I32 value);
        void ShaderSetUniformU32(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::U32 value);
        void ShaderSetUniformF32(Progator::Objects::Shader* shader, Progator::Base::Renderer* renderer, const Progator::Types::Basic::CH8* key, const Progator::Types::Basic::F32 value);
    };
};

#endif