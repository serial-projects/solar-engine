#ifndef ProgatorBackendsOpenGLTypes_hpp
#define ProgatorBackendsOpenGLTypes_hpp

#include "Progator/Types.hpp"
#include <GL/glew.h>

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            /// @brief Set certain object types here since OpenGL uses all GLuint for everything,
            /// this will improve a lot the code readability.
            namespace Types
            {
                typedef GLuint VertexBufferObject;
                typedef GLuint VertexAttributeObject;

                typedef GLuint AnyShader;
                typedef GLuint VertexShader;
                typedef GLuint FragmentShader;
                typedef GLuint GeometryShader;
                typedef GLuint ShaderProgram;

                typedef GLuint Texture2D;
                typedef GLuint Texture3D;
            };
        };
    };
};

#endif