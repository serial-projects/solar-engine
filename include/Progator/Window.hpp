#ifndef ProgatorWindow_hpp
#define ProgatorWindow_hpp

#include "Progator/Pointers.hpp"

namespace Progator
{
    typedef struct Window
    {
        void*                   backend;
        Progator::Pointers*     pointers;
        Progator::Validator*    validator;
        Progator::U16           width;
        Progator::U16           height;
    } Window;
    Progator::Window* WindowNew();
    void WindowDestroy(Progator::Window* window);
    void WindowInit(Progator::Window* window, Progator::Pointers* pointers, Progator::Validator* validator);
    void WindowSetSize(Progator::Window* window, const Progator::U16 width, const Progator::U16 height);
    void WindowSetTitle(Progator::Window* window, const Progator::Character *title);
    void WindowSetVerticalSync(Progator::Window* window, const Progator::U8 enable);
    void WindowSetIcon(Progator::Window* window, const Progator::Character* path);
    void WindowDraw(Progator::Window* window);
};

#endif