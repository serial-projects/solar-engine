#include "Solar/Instance.hxx"
#include "Solar/Utils.hxx"
#include "Solar/Core/Window.hxx"
#include "Solar/GL.hxx"

void Solar::Instance::Init()
{
    WHEN(SDL_Init(SDL_INIT_EVERYTHING) < 0, GENERROR("failed to initialize SDL due: " << SDL_GetError()));
    
    // TODO: select mode here, opengl or vulkan?
    shared_core.window.InitializeOpenGL(1280, 720);
    shared_core.window.SetTitle("Solar Engine");

    // initialize the OpenGL pointers!
    this->InitializeOpenGL();
    
    // Set the directory:
    this->shared_core.content_provider.resource_path = "./Solar/";

    // Set the scene:
    this->scene_mode.Init(&this->shared_core);

    // Say some hello:
    GENDEBUG("Solar is running on \"" << glGetString(GL_RENDERER) << "\", vendor: \"" << glGetString(GL_VENDOR) << "\"");
    GENDEBUG("Running on OpenGL " << glGetString(GL_VERSION) << ", GLSL Version: \"" << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\"");
}

void Solar::Instance::InitializeOpenGL()
{
    glewExperimental = GL_TRUE;
    MAKESURE(glewInit() == GLEW_OK, GENERROR("failed to initialize GLEW!"));
}

void SolarInstance_ShowTickDebugInformation(Solar::Instance *instance, Solar::Types::U64 dlt)
{
    GENDEBUG("Current Delta Time: " << dlt << ", expected = " << (1000 / instance->shared_core.framerate));
    GENDEBUG("Current Tick: " << instance->shared_core.tick_counter << " / Framerate: " << instance->shared_core.framerate);
    GENDEBUG("There are " << instance->shared_core.content_provider.cached_shaders.size() << " cached shaders;");
}

void Solar::Instance::Loop()
{
    Solar::Types::U64 ltm = SDL_GetTicks64();
    while(SolarCoreSharedMode_GetRunning(this->shared_core.mode))
    {
        // NOTE: even though the screen may refresh on different mode, keep
        // in mind the logic is not and thus, keep it on 60 FPS or whatever
        // defined by the configuration.
        Solar::Types::U64 now=SDL_GetTicks64();
        Solar::Types::U64 dlt=(now - ltm);
        WHEN(dlt >= (1000 / this->shared_core.framerate), {
            this->Tick();
            WHEN(SolarCoreSharedMode_GetDebug(this->shared_core.mode), SolarInstance_ShowTickDebugInformation(this, dlt));
            ltm = now;
        });
        this->Draw();
    }
}

void Solar::Instance::Tick()
{
    if(SolarCoreSharedMode_GetDoTick(this->shared_core.mode))
    {
        this->scene_mode.Tick();
        this->shared_core.tick_counter++;
    }
    else SolarCoreSharedMode_ToggleDoTick(this->shared_core.mode);
}

void SolarInstance_ShowDrawDebugInformation(Solar::Instance *instance)
{
    GENDEBUG("Current Draw: " << instance->shared_core.draw_counter);
    GENDEBUG("Free Camera Position: " << glm::to_string(instance->scene_mode.free_camera.position));
}

void Solar::Instance::Draw()
{
    if(SolarCoreSharedMode_GetDoDraw(this->shared_core.mode))
    {
        this->scene_mode.Draw();
        SDL_GL_SwapWindow(this->shared_core.window.os_window);
        this->shared_core.draw_counter++;
    }
    else SolarCoreSharedMode_ToggleDoDraw(this->shared_core.mode);
    WHEN(SolarCoreSharedMode_GetDebug(this->shared_core.mode), SolarInstance_ShowDrawDebugInformation(this));
}

void Solar::Instance::Quit()
{
    // Quit from the modes:
    this->scene_mode.Quit();

    // Quit from the Window:
    
    this->shared_core.content_provider.Clean();
    this->shared_core.window.QuitOpenGL();
    SDL_Quit();
}