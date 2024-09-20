#ifndef ProgatorBackendsOpenGLBasics_hpp
#define ProgatorBackendsOpenGLBasics_hpp

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Progator/Support/Math.hpp"
#include "Progator/Types.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            typedef GLuint  VBO;
            typedef GLuint  VAO;
            typedef GLuint  VertexShader;
            typedef GLuint  FragmentShader;
            typedef GLuint  ShaderProgram;
            typedef GLuint  Texture;
            typedef GLuint  Framebuffer;
        };
    };
};

#endif