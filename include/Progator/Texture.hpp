#ifndef ProgatorTexture_hpp
#define ProgatorTexture_hpp

#include "Progator/Types.hpp"
#include "Progator/Validator.hpp"
#include "Progator/Pointers.hpp"

namespace Progator
{
    typedef struct Texture
    {
        void *backend;
        Progator::Pointers* pointers;
        Progator::Validator* validator;
    } Texture;
    Progator::Texture* TextureNew();
    void TextureDestroy(Progator::Texture* texture);
    void TextureInit(Progator::Texture* texture, Progator::Pointers* pointers, Progator::Validator* validator);
    void TextureLoadFromFile(Progator::Texture* texture, const Progator::Character* path);
    void TextureUse(Progator::Texture* texture);
};

#endif