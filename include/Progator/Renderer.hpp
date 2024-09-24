#ifndef ProgatorRenderer_hpp
#define ProgatorRenderer_hpp

#include "Progator/Types.hpp"
#include "Progator/Pointers.hpp"
#include "Progator/Validator.hpp"

namespace Progator
{
    typedef struct Renderer
    {
        void*                   backend;
        Progator::Pointers*     pointers;
        Progator::Validator*    validator;

        /* NOTE: keep some information about the viewport: */
        Progator::U16           width;
        Progator::U16           height;
        Progator::U16           x;
        Progator::U16           y;
    } Renderer;

    Progator::Renderer* RendererNew();
    void RendererDestroy(Progator::Renderer* renderer);
    void RendererInit(Progator::Renderer* renderer, Progator::Pointers* pointers, Progator::Validator* validator);
    void RendererSetViewport(Progator::Renderer* renderer, const Progator::U16 width, const Progator::U16 height, const Progator::U16 x, const Progator::U16 y);
    void RendererClear(Progator::Renderer* renderer, const Progator::RGBA84 color);
    void RendererDraw(Progator::Renderer* renderer);
};

#endif