#ifndef solar_gl_hxx
#define solar_gl_hxx

#include <GL/glew.h>
#define GLEW_STATIC 1

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace Solar
{
    namespace GL
    {
        typedef GLuint VertexShader;
        typedef GLuint FragmentShader;
        typedef GLuint ShaderProgram;
        typedef GLuint VertexBufferObject;
        typedef GLuint VertexAttribObject;
        typedef GLuint ElementBufferObject;
    };
};

#endif
// Solar/GL.hxx: