#include "Solar/Instance/Init.hpp"

void Solar::InstanceInit(
    Solar::Instance* instance
)
{
    Solar::Core::SharedInit(&instance->shared_core);
}