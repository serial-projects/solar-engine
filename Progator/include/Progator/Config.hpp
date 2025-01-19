#ifndef ProgatorConfig_hpp
#define ProgatorConfig_hpp

// General Information:
#define PROGATOR_VERSION                        10000
#define PROGATOR_VERSION_STR                    "1.0.000"
#define PROGATOR_VERSION_CODENAME               "Ghost"
#define PROGATOR_VERSION_FULLNAME               "Progator $ " PROGATOR_VERSION_STR " (" PROGATOR_VERSION_CODENAME ")"

// Debugging?
#define PROGATOR_DEBUG

// Defined Supported Backends:

#define PROGATOR_BACKEND_OPENGL
// #define PROGATOR_BACKEND_VULKAN
// #define PROGATOR_BACKEND_DIRECTX
// #define PROGATOR_BACKEND_METAL
// #define PROGATOR_BACKEND_GLES

// Progator/Backends/OpenGL/Window.hpp:

// Progator/Backends/OpenGL/Renderer.cpp:
#define PROGATOR_BACKENDS_OPENGL_RENDERER_MAJOR_VERSION         3
#define PROGATOR_BACKENDS_OPENGL_RENDERER_MINOR_VERSION         3

#endif