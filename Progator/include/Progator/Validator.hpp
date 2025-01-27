#ifndef ProgatorValidator_hpp 
#define ProgatorValidator_hpp

namespace Progator
{
    namespace ValidatorCodes
    {
        enum ValidatorCodes
        {
            /// @brief Nothing.
            Ok = 0,
            
            /* General Errors (on Base/Object): */
            FailedInitializeSDL,

            /// @brief For bad memory errors.
            BadAllocation,

            /* OpenGL backends: */
            
            /// @brief For when the SDL itself failing to create an window.
            FailedInitializeOpenGLBackendDueSDLWindowCreateError,

            /// @brief For when the OpenGL itself could not be created.
            FailedInitializeOpenGLBackendDueBadOpenGLContext,

            /// @brief For when the GLEW did not initialize.
            FailedInitializeOpenGLBackendDueBadGLEWInit,

            /// @brief For when the vertex shaders doesn't compile.
            FailedCompileVertexShader,

            /// @brief For when the fragment shader doesn't compile.
            FailedCompileFragmentShader,

            /// @brief For when the geometry shader doesn't compile.
            FailedCompileGeometryShader,

            /// @brief When linking failed.
            FailedLinkShaders,

            /// @brief Exclusive for when the ShaderUse() fails.
            FailedUseShaders,

            /// @brief For impossible errors.
            Unknown = UINT8_MAX
        };
    };
};

#endif