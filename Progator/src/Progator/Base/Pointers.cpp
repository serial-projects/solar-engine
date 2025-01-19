#include "Progator/Base/Pointers.hpp"
#include "Progator/Backends.hpp"

Progator::Base::Pointers Progator::Base::PointersNew()
{
    Progator::Base::Pointers pointers;
    return pointers;
}

void Progator::Base::PointersDestroy(
    Progator::Base::Pointers* pointers
)
{
    /* NOTE: nothing to be done since everything on the stack! */
    return;
}

void Progator::Base::PointersInit(
    Progator::Base::Pointers* pointers
)
{
    /* Set the mode: */
    pointers->mode = Progator::Base::PointersBackend::NoBackend;
    
    /* Window Pointers: */
    pointers->window_new = nullptr;
    pointers->window_destroy = nullptr;
    pointers->window_init = nullptr;
    pointers->window_set_size = nullptr;
    pointers->window_set_position = nullptr;
    pointers->window_set_title = nullptr;
    pointers->window_set_icon = nullptr;
    pointers->window_get_identity = nullptr;

    /* Renderer Pointers: */
    pointers->renderer_new = nullptr;
    pointers->renderer_destroy = nullptr;
    pointers->renderer_init = nullptr;
    pointers->renderer_attach_another_window = nullptr;
    pointers->renderer_use = nullptr;
    pointers->renderer_set_viewport = nullptr;
    pointers->renderer_adjust_vertical_synchronization = nullptr;
    pointers->renderer_clear = nullptr;
    pointers->renderer_draw = nullptr;
}

// (A)ssign (V)alue to (O)penGL (Backend)
#define AVO(key, bn)                                                                                \
    pointers->key = (Progator::Base::BackendBinding::bn)(Progator::Backends::OpenGL::bn);

void Progator::Base::PointersSetOpenGLMode(
    Progator::Base::Pointers* pointers
)
{
    /* Set the mode: */
    pointers->mode = Progator::Base::PointersBackend::OpenGL;
    
    /* Set the window: */
    AVO(window_new, WindowNew);
    AVO(window_destroy, WindowDestroy);
    AVO(window_init, WindowInit);
    AVO(window_set_size, WindowSetSize);
    AVO(window_set_position, WindowSetPosition);
    AVO(window_set_icon, WindowSetIcon);
    AVO(window_get_identity, WindowGetIdentity);

    /* Set the renderer: */
    AVO(renderer_new, RendererNew);
    AVO(renderer_destroy, RendererDestroy);
    AVO(renderer_init, RendererInit);
    AVO(renderer_attach_another_window, RendererAttachAnotherWindow);
    AVO(renderer_use, RendererUse);
    AVO(renderer_set_viewport, RendererSetViewport);
    AVO(renderer_adjust_vertical_synchronization, RendererAdjustVerticalSynchronization);
    AVO(renderer_clear, RendererClear);
    AVO(renderer_draw, RendererDraw);
}