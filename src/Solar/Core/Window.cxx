#include "Solar/Core/Window.hxx"
#include "Solar/Utils.hxx"
#include "Solar/Config.hxx"

namespace Solar
{
    namespace Core
    {
        namespace Window
        {
            // BasicSDL operations:
            void BasicSDLWindow::InitializeSDL(const Solar::Core::Window::WindowSize width, const Solar::Core::Window::WindowSize height, const Solar::Types::U32 params)
            {
                this->os_window = SDL_CreateWindow(
                    "BasicSDLWindow",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    width,
                    height,
                    params
                );
                MAKESURE(this->os_window != NULL, GENERROR("failed to open SDL window due: " << SDL_GetError()));
                // NOTE: adjust the vsync on very early stages:
                SDL_GL_SetSwapInterval(SOLAR_CORE_WINDOW_VSYNC_MODE);
                this->width = width;
                this->height= height;
            }
            
            void BasicSDLWindow::InitializeOpenGL(const Solar::Core::Window::WindowSize width, const Solar::Core::Window::WindowSize height)
            {
                // Set all the opengl attributes before creating the window:
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

                // Initialize SDL (which will initialize our OS Window):
                this->InitializeSDL(width, height, SDL_WINDOW_OPENGL);
                this->gl_context = SDL_GL_CreateContext(this->os_window);
                MAKESURE(this->gl_context != NULL, GENERROR("failed to open an OpenGL context due: " << SDL_GetError()));
            }

            void BasicSDLWindow::SetTitle(const Solar::Types::Character *title)
            {
                SDL_SetWindowTitle(this->os_window, title);
            }

            void BasicSDLWindow::QuitOpenGL()
            {
                SDL_GL_DeleteContext(this->gl_context);
                this->QuitSDL();
            }

            void BasicSDLWindow::QuitSDL()
            {
                SDL_DestroyWindow(this->os_window);
            }
        };

    };
};