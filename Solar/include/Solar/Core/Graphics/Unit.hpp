#ifndef SolarCoreGraphicsUnit_hpp
#define SolarCoreGraphicsUnit_hpp

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Core
    {
        namespace Graphics
        {
            /// @brief An GraphicsUnit is a fancy name for an window, usually everything on the game 
            /// is rendered on the 'main' display. In a instance, there can be multiple displays or 
            /// units that can be used to show information.
            struct Unit
            {
                Logica::Control::Validator  validator;
                Progator::Base::Pointers    pointers;
                Progator::Base::Window*     window;
                Progator::Base::Renderer*   renderer;
            };

            Solar::Core::Graphics::Unit* UnitNew();
            void UnitDestroy(Solar::Core::Graphics::Unit* unit);
            void UnitInit(Solar::Core::Graphics::Unit* unit, const Solar::Types::Basic::U8 mode);
        };
    };
};

#endif