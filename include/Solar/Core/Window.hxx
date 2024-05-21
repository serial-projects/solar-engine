#ifndef solar_core_window_hxx
#define solar_core_window_hxx

#include "Solar/GL.hxx"
#include "Solar/Types.hxx"

namespace Solar
{
    namespace Core
    {
        namespace Window
        {
            typedef Solar::Types::U16 WindowSize;

            // Basic SDLWindow, can be integrated into OpenGL & Vulkan on the future.
            class BasicSDLWindow
            {
                public:
                    SDL_Window          *os_window;
                    SDL_GLContext       gl_context;
                    Solar::Core::Window::WindowSize width = 0;
                    Solar::Core::Window::WindowSize height= 0;

                    void InitializeSDL(const Solar::Core::Window::WindowSize width, const Solar::Core::Window::WindowSize height, const Solar::Types::U32 params);
                    void InitializeOpenGL(const Solar::Core::Window::WindowSize width, const Solar::Core::Window::WindowSize height);
                    void InitializeVulkan(const Solar::Core::Window::WindowSize width, const Solar::Core::Window::WindowSize height);
                    void Init(const Solar::Core::Window::WindowSize width, const Solar::Core::Window::WindowSize height);
                    void SetTitle(const Solar::Types::Character *title);
                    void QuitOpenGL();
                    void QuitVulkan();
                    void QuitSDL();
            };
        };
    };
};

#endif