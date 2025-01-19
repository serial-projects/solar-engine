#ifndef ProgatorValidator_hpp 
#define ProgatorValidator_hpp

namespace Progator
{
    namespace ValidatorCodes
    {
        enum ValidatorCodes
        {
            /// @brief Nothing.
            No = 0,
            
            /* General Errors (on Base/Object): */

            /// @brief For bad memory errors.
            BadAllocation,

            /* OpenGL backends: */
            
            /// @brief For when the SDL itself failing to create an window.
            FailedInitializeOpenGLBackendDueSDLWindowCreateError,

            /// @brief For when the OpenGL itself could not be created.
            FailedInitializeOpenGLBackendDueBadOpenGLContext,

            /// @brief For when the GLEW did not initialize.
            FailedInitializeOpenGLBackendDueBadGLEWInit,

            /// @brief For impossible errors.
            Unknown = UINT8_MAX
        };
    };
};

#endif