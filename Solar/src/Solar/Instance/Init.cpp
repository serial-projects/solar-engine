#include "Solar/Instance/Init.hpp"

void Solar::InstanceInit(
    Solar::Instance* instance
)
{
    Solar::Core::SharedInit(&instance->shared_core);
    Solar::Modes::Scene::ModeInit(&instance->scene_mode, &instance->shared_core);
}