#ifndef ProgatorObjectsBuffersUniform_hpp
#define ProgatorObjectsBuffersUniform_hpp

#include "Progator/Types.hpp"
#include "Progator/Base/Pointers.hpp"
#include "Progator/Base/Renderer.hpp"

// NOTE: this takes the shader as direct parameter.
#include "Progator/Objects/Shader.hpp"

namespace Progator
{
    namespace Objects
    {
        namespace Buffers
        {
            struct Uniform
            {
                void* backend;
                Progator::Base::Pointers* pointers;
                Logica::Control::Validator* validator;
            };
            Progator::Objects::Buffers::Uniform* UniformNew();
            void UniformDestroy(Progator::Objects::Buffers::Uniform* uniform, Progator::Base::Renderer* renderer);
            void UniformInit(Progator::Objects::Buffers::Uniform* uniform, Progator::Base::Pointers* pointers, Progator::Base::Renderer* renderer, Logica::Control::Validator* validator);
            void UniformAttachShader(Progator::Objects::Buffers::Uniform* uniform, Progator::Base::Renderer* renderer, Progator::Objects::Shader* shader, const Progator::Types::Specifics::UBO::Property property);
            void UniformSetData(Progator::Objects::Buffers::Uniform* uniform, Progator::Base::Renderer* renderer, const Progator::Types::Specifics::UBO::Property property, void* data, Progator::Types::Basic::U64 size);
        };
    };
};

#endif