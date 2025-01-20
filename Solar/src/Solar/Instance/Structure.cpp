#include "Solar/Instance/Structure.hpp"

Solar::Instance Solar::InstanceNew()
{
    Solar::Instance instance;
    return instance;
}

void Solar::InstanceDestroy(
    Solar::Instance* instance
)
{
    /* Destroy the instance: */
    Solar::Core::SharedDestroy(&instance->shared_core);
}