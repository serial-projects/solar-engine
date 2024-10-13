#include "Progator/Texture.hpp"

Progator::Texture* Progator::TextureNew()
{
    Progator::Texture* proto = new Progator::Texture;
    return proto;
}

void Progator::TextureDestroy(Progator::Texture* texture)
{
    texture->pointers->texture_destroy(texture->backend);
    delete texture;
}

void Progator::TextureInit(Progator::Texture* texture, Progator::Pointers* pointers, Progator::Validator* validator)
{
    texture->validator = validator;
    texture->pointers = pointers;

    texture->backend = texture->pointers->texture_new();
    if(texture->backend == nullptr)
    {
        Progator::ValidatorError(
            texture->validator,
            Progator::ValidatorCodes::FailedToCreateObject,
            "Failed to create texture object."
        );
    }
    else
    {
        texture->pointers->texture_init(
            texture->backend,
            texture->validator
        );
    }
}

void Progator::TextureLoadFromFile(Progator::Texture* texture, const Progator::Character* path)
{
    ProgatorHelperPerformWhenValidated(
        texture->validator,
        {
            texture->pointers->texture_load_from_file(
                texture->backend,
                path
            );
        }
    );
}

void Progator::TextureUse(Progator::Texture* texture)
{
    ProgatorHelperPerformWhenValidated(
        texture->validator,
        {
            texture->pointers->texture_use(
                texture->backend
            );
        }
    );
}