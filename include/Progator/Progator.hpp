#ifndef Progator_hpp
#define Progator_hpp

#define PROGATOR_INCLUDED
#include "Progator/Values.hpp"

/* PROGATOR_VERSIONING:
 * This holds the version of the progator project and some information.
 */

#define PROGATOR_VERSION                "1.0.00"
#define PROGATOR_VERSION_NUMBER         1000
#define PROGATOR_AUTHOR                 "Pipes Studios"
#define PROGATOR_LICENSE                "GPLv2"

/* PROGATOR_SUPPORTS_<API>:
 * This holds the information if an current version of the Progator supports an API and that can
 * be used without causing segmentation faults.
 */

#define PROGATOR_SUPPORTS_OPENGL        PROGATOR_SUPPORTED_API
#define PROGATOR_SUPPORTS_VULKAN        PROGATOR_NOT_SUPPORTED_API
#define PROGATOR_SUPPORTS_METAL         PROGATOR_NOT_SUPPORTED_API
#define PROGATOR_SUPPORTS_GLES          PROGATOR_NOT_SUPPORTED_API
#define PROGATOR_SUPPORTS_DX            PROGATOR_NOT_SUPPORTED_API

/* Everything is SDL2 Guided, so export it here before. 
 */

#include <SDL2/SDL.h>

/* Begin Exporting the Headers:
 */

#include "Progator/Validator.hpp"
#include "Progator/Pointers.hpp"
#include "Progator/Types.hpp"
#include "Progator/Renderer.hpp"
#include "Progator/Window.hpp"

namespace Progator
{
    void Init(Progator::Validator* validator);
    void Quit();
};

#endif