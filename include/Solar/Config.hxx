#ifndef solar_config_hxx
#define solar_config_hxx

// Solar/Core/Window.hxx:

// NOTE: according to the SDL:
// Some systems allow specifying -1 for the interval, to enable adaptive vsync. 
// Adaptive vsync works the same as vsync, but if you've already missed the 
// vertical retrace for a given frame, it swaps buffers immediately, which might
// be less jarring for the user during occasional framerate drops. 
// So, set to 1 to prevent future problems:
#define SOLAR_CORE_WINDOW_VSYNC_MODE    1

// Solar/Core/Storage.hxx:

// Amount of characters to handle the log from exceptions on OpenGL shader tool,
// on debug stages, you should run an third-party tool like shader validator.
#define SOLAR_CORE_STORAGE_SHADER_ERRLOGSIZE 256

#endif
// Solar/Config.hxx