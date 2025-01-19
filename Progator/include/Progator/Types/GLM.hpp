#ifndef ProgatorTypesGLM_hpp
#define ProgatorTypesGLM_hpp

#ifndef ProgatorSupportGLM_hpp
#define ProgatorSupportGLM_hpp

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/io.hpp>

namespace Progator
{
    namespace Types
    {
        namespace GLM
        {
            typedef glm::vec4 Vector4;
            typedef glm::vec3 Vector3;
            typedef glm::vec2 Vector2;

            typedef glm::mat4 Matrix44;
            typedef glm::mat3 Matrix33;
            typedef glm::mat2 Matrix22;
        };
    };
};

#endif