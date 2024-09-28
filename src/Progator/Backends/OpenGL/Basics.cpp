#include "Progator/Backends/OpenGL/Basics.hpp"
#include <cstdio>

/*
 * NOTE: for debug reasons, print everything OpenGL has to say.
 */
void Progator::Backends::OpenGL::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* uparameters)
{
    std::printf(
        "GL_CALLBACK: %s type: 0x%x, severity = 0x%x [%s], message = %s\n",
        ( 
            type == GL_DEBUG_TYPE_ERROR ?                   "** GL_ERROR **"                    : 
            type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR ?     "** GL_DEPRECATED_BEHAVIOR **"      :
            type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR ?      "** GL_UNDEFINED_BEHAVIOR ** "      :
            type == GL_DEBUG_TYPE_PORTABILITY ?             "** GL_PORTABILITY **"              :
            type == GL_DEBUG_TYPE_MARKER ?                  "** GL_MARKER **"                   :
            type == GL_DEBUG_TYPE_PUSH_GROUP ?              "** GL_PUSH_GROUP **"               :
            type == GL_DEBUG_TYPE_POP_GROUP ?               "** GL_POP_GROUP **"                :
            type == GL_DEBUG_TYPE_OTHER ?                   "** GL_OTHER **"                    :
                                                            "** ??? **"
        ),
        type,
        severity,
        (
            severity == GL_DEBUG_SEVERITY_LOW ?             "LOW"       :
            severity == GL_DEBUG_SEVERITY_MEDIUM ?          "MEDIUM"    :
            severity == GL_DEBUG_SEVERITY_HIGH ?            "HIGH"      :
            severity == GL_DEBUG_SEVERITY_NOTIFICATION ?    "NOTE"      :
                                                            "???"
        ),
        message
    );
}