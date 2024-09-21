#ifndef ProgatorBackendsOpenGLTexture_hpp
#define ProgatorBackendsOpenGLTexture_hpp

#include "Progator/Backends/OpenGL/Basics.hpp"
#include "Progator/Validator.hpp"

namespace Progator
{
    namespace Backends
    {
        namespace OpenGL
        {
            typedef struct Texture
            {
                Progator::Backends::OpenGL::Texture2D texture;
                Progator::Validator* validator;
            } Texture;
            Progator::Backends::OpenGL::Texture* TextureNew();
            void TextureDestroy(Progator::Backends::OpenGL::Texture* texture);
            void TextureInit(Progator::Backends::OpenGL::Texture* texture, Progator::Validator* validator);
            void TextureLoadFromFile(Progator::Backends::OpenGL::Texture* texture, const Progator::Character* path);
            void TextureUse(Progator::Backends::OpenGL::Texture* texture);
        };
    };
};

#endif