#include "Progator/Backends/OpenGL/Renderer.hpp"

Progator::Backends::OpenGL::Renderer* Progator::Backends::OpenGL::RendererNew()
{
    Progator::Backends::OpenGL::Renderer* proto = new Progator::Backends::OpenGL::Renderer;
    return proto;
}

void Progator::Backends::OpenGL::RendererDestroy(Progator::Backends::OpenGL::Renderer* renderer)
{
    delete renderer;
}

void Progator::Backends::OpenGL::RendererInit(Progator::Backends::OpenGL::Renderer* renderer, Progator::Validator* validator)
{
    renderer->validator = validator;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
}

void Progator::Backends::OpenGL::RendererSetViewport(Progator::Backends::OpenGL::Renderer *backend, const Progator::U16 width, const Progator::U16 height, const Progator::U16 x, const Progator::U16 y)
{
    glViewport(
        (GLint)x,
        (GLint)y,
        (GLsizei)width,
        (GLsizei)height
    );
}

void Progator::Backends::OpenGL::RendererClear(Progator::Backends::OpenGL::Renderer* backend, const Progator::RGBA84 color)
{
    /* Shift the colors to adquire an channel ranging from 0 - 255. (RGBA Color Space). */
    const Progator::U8 R = ((color & 0xFF000000) >> 24);
    const Progator::U8 G = ((color & 0x00FF0000) >> 16);
    const Progator::U8 B = ((color & 0x0000FF00) >>  8);
    const Progator::U8 A = ((color & 0x000000FF));

    glClearColor(
        (float)R / (float)255,
        (float)G / (float)255,
        (float)B / (float)255,
        (float)A / (float)255
    );

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );
}

void Progator::Backends::OpenGL::RendererDraw(Progator::Backends::OpenGL::Renderer *backend)
{
    /* NOT NECESSARY ON OPENGL: */
}