#ifndef SolarCoreGraphics_hpp
#define SolarCoreGraphics_hpp

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Core
    {
        struct Graphics
        {
            Progator::Base::Pointers pointers;
            Progator::Base::Window window;
            Progator::Base::Renderer renderer;
            Logica::Control::Validator validator;
        };
        Solar::Core::Graphics GraphicsNew();
        void GraphicsDestroy(Solar::Core::Graphics* graphics);
        void GraphicsInit(Solar::Core::Graphics* graphics);
    };
};

#endif