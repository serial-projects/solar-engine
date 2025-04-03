#ifndef ProgatorTypesSpecificsPointers_hpp
#define ProgatorTypesSpecificsPointers_hpp

/* NOTE: have the fun. */
#include <functional>

#include "Progator/Types/Specifics.hpp"
#include "Progator/Types/Basic.hpp"
#include "Logica/Logica.hpp"

/* NOTE: This file doesn't respect the 100 line column rule so... :( */

namespace Progator
{
    namespace Types
    {
        namespace Specifics
        {
            namespace Pointers
            {
                /**
                 * \brief Contains all the functions connectors to the Backend <-> Base.
                 */
                namespace Integration
                {
                    /**
                     * \brief Contains the window.
                     */
                    namespace Window
                    {

                        typedef std::function<void*()>                                                          New;
                        typedef std::function<void(void*)>                                                      Destroy;
                        typedef std::function<void(void*, Logica::Control::Validator*)>                         Init;
                        typedef std::function<void(void*, Progator::Types::Specifics::Window::Geometry)>        SetGeometry;
                        typedef std::function<void(void*, const Progator::Types::Basic::CH8*)>                  SetTitle;
                    };

                    /**
                     * \brief Contains the renderer.
                     */
                    namespace Renderer
                    {
                        typedef std::function<void*()>                                                          New;
                        typedef std::function<void(void*)>                                                      Destroy;
                        typedef std::function<void(void*,void*, Logica::Control::Validator*)>                   Init;
                        typedef std::function<void(void*, Progator::Types::Specifics::Renderer::Viewport)>      SetViewport;
                        typedef std::function<void(void*, Progator::Types::Basic::Boolean)>                     SetVerticalSynchronization;
                        typedef std::function<void(void*, void*)>                                               AttachWindow;
                        typedef std::function<void(void*)>                                                      Use;
                        typedef std::function<void(void*, Progator::Types::Basic::U32)>                         Clear;
                        typedef std::function<void(void*)>                                                      Draw;
                    };
                };
            };
        };
    };
};

#endif