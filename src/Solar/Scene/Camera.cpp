#include "Solar/Scene/Camera.hpp"

Solar::Scene::FreeCamera Solar::Scene::FreeCameraNew()
{
    Solar::Scene::FreeCamera camera;
    Solar::Scene::FreeCameraUpdateVectors(&camera);

    /* return the camera: */
    return camera;
}

Solar::Matrix44 Solar::Scene::FreeCameraGetViewMatrix(Solar::Scene::FreeCamera* camera)
{
    Solar::Matrix44 result = glm::lookAt(camera->position, camera->position + camera->front, camera->up);
    return result;
}

void Solar::Scene::FreeCameraSetLooking(Solar::Scene::FreeCamera* camera, Solar::F32 xoffset, Solar::F32 yoffset)
{
    /* NOTE: from SDL, handle if the mouse is actually being used. */
    Solar::I32 xpos; Solar::I32 ypos;
    Solar::U32 state = SDL_GetMouseState(&xpos, &ypos);
    if(state == SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        /* Set the mouse to hidden view: */
        SDL_ShowCursor(SDL_FALSE);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        xoffset *= camera->mov_sensitivity;
        yoffset *= camera->mov_sensitivity;
        camera->yaw         += xoffset;
        camera->pitch       += yoffset;

        /* LOCK the player to prevent from flipping: */
        if(camera->pitch > 89.0f)   camera->pitch = 89.0f;
        if(camera->pitch < -89.0f)  camera->pitch = -89.0f;
        Solar::Scene::FreeCameraUpdateVectors(camera);
    }
    else
    {
        /* Set the mouse to the normal state: */
        SDL_ShowCursor(SDL_TRUE);
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

void Solar::Scene::FreeCameraSetPosition(Solar::Scene::FreeCamera* camera, const Solar::U8 direction)
{
    /* NOTE: from the original source (learnopengl.com), there is a delta time here BUT
     * since the engine is locked at 60 TPS, there is no need to calculate this.
     */
    const Solar::F32 velocity = camera->mov_speed;
    switch(direction)
    {
        case 0: camera->position += camera->front * velocity;   break;
        case 1: camera->position -= camera->front * velocity;   break;
        case 2: camera->position -= camera->right * velocity;   break;
        case 3: camera->position += camera->right * velocity;   break;
        default:                                                break;
    };
}

void Solar::Scene::FreeCameraUpdateVectors(Solar::Scene::FreeCamera* camera)
{
    glm::vec3 new_front;
    new_front.x = std::cos(glm::radians(camera->yaw)) * std::cos(glm::radians(camera->pitch));
    new_front.y = std::sin(glm::radians(camera->pitch));
    new_front.z = std::sin(glm::radians(camera->yaw)) * std::cos(glm::radians(camera->pitch));
    camera->front = glm::normalize(new_front);
    camera->right = glm::normalize(glm::cross(camera->front, camera->world_up));
    camera->up    = glm::normalize(glm::cross(camera->right, camera->front));
}