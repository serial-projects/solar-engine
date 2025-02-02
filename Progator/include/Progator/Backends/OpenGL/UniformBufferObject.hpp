#ifndef ProgatorBackendsOpenGLUniformBufferObject_hpp
#define ProgatorBackendsOpenGLUniformBufferObject_hpp

#include "Progator/Backends/OpenGL/Types.hpp"
#include "Progator/Backends/OpenGL/Renderer.hpp"
#include "Progator/Backends/OpenGL/Shader.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            struct UniformBufferObject
            {
                Progator::Backends::OpenGL::Types::UniformBufferObject buffer;
                Logica::Control::Validator* validator;
            };
            Progator::Backends::OpenGL::UniformBufferObject* UniformBufferObjectNew();
            void UniformBufferObjectDestroy(Progator::Backends::OpenGL::UniformBufferObject* ubo, Progator::Backends::OpenGL::Renderer* renderer);
            void UniformBufferObjectInit(Progator::Backends::OpenGL::UniformBufferObject* ubo, Progator::Backends::OpenGL::Renderer* renderer, Logica::Control::Validator* validator);
            void UniformBufferObjectAttachShader(Progator::Backends::OpenGL::UniformBufferObject* ubo, Progator::Backends::OpenGL::Renderer* renderer, Progator::Backends::OpenGL::Shader* shader, const Progator::Types::Specifics::UBO::Property property);
            void UniformBufferObjectSetData(Progator::Backends::OpenGL::UniformBufferObject* ubo, Progator::Backends::OpenGL::Renderer* renderer, const Progator::Types::Specifics::UBO::Property property, void* data, Progator::Types::Basic::U64 size);
        };
    };
};

#endif