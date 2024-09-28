#include "Progator/Backends/OpenGL/Texture.hpp"

/*
 * NOTE: Here is required to have SDL_Image on your compilation.
 */

#include <SDL2/SDL_image.h>

Progator::Backends::OpenGL::Texture* Progator::Backends::OpenGL::TextureNew()
{
    Progator::Backends::OpenGL::Texture* proto = new Progator::Backends::OpenGL::Texture;
    return proto;
}

void Progator::Backends::OpenGL::TextureDestroy(Progator::Backends::OpenGL::Texture* texture)
{
    glDeleteTextures(1, &texture->texture);
    delete texture;
}

void Progator::Backends::OpenGL::TextureInit(Progator::Backends::OpenGL::Texture* texture, Progator::Validator* validator)
{
    texture->validator = validator;
    glGenTextures(1, &texture->texture);
}


void Progator::Backends::OpenGL::TextureLoadFromFile(Progator::Backends::OpenGL::Texture* texture, const Progator::Character* path)
{
    SDL_Surface* image = IMG_Load(path);
    if(image == NULL)
    {
        /* TODO: use validator now: */
        abort();
    }
    else
    {
        const Progator::U32 texmode = image->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, texture->texture);
    
        /* TODO: let the user be able to customize this:
         */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            texmode,
            image->w, image->h,
            0,
            texmode,
            GL_UNSIGNED_BYTE,
            image->pixels
        );
    
        /* TODO: check for possible OpenGL errors here: */
        glGenerateMipmap(GL_TEXTURE_2D);
        
        /* done: */
        SDL_FreeSurface(image);
    }
}

void Progator::Backends::OpenGL::TextureUse(Progator::Backends::OpenGL::Texture* texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->texture);
    glActiveTexture(GL_TEXTURE0);
}