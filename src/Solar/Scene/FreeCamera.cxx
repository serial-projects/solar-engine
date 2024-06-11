#include "Solar/Scene/FreeCamera.hxx"
#include "Solar/Utils.hxx"
#include <cmath>

void Solar::Scene::FreeCamera::Init(Solar::Core::Shared *shared_core)
{
    this->position      = glm::vec3(0.0f);
    this->worldup       = glm::vec3(0.0f, 1.0f, 0.0f);
    this->yaw           = -90.0f;
    this->pitch         = 0.0f;
    this->speed         = 0.1f;
    this->sensitivity   = 0.3f;
    this->front         = glm::vec3(0.0f, 0.0f, -1.0f);
    
    // SDL_SetRelativeMouseMode(SDL_TRUE);

    //SDL_SetWindowMouseGrab(shared_core->window.os_window, SDL_TRUE);
    this->UpdateCameraVectors();
}

void Solar::Scene::FreeCamera::Quit()
{
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

glm::mat4 Solar::Scene::FreeCamera::GetViewMatrix()
{
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Solar::Scene::FreeCamera::UpdateCameraVectors()
{
    glm::vec3 new_front;
    new_front.x = std::cos(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));
    new_front.y = std::sin(glm::radians(this->pitch));
    new_front.z = std::sin(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));
    this->front = glm::normalize(new_front);
    // NOTE: re-process the other vectors:
    this->right = glm::normalize(glm::cross(this->front, this->worldup));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}

void Solar::Scene::FreeCamera::ProcessMouse(const Solar::Types::I8 xoffset, const Solar::Types::I8 yoffset) {
    Solar::Types::I32 mouse_x, mouse_y;
    Solar::Types::U32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
    // NOTE: finally rotate the camera!
    // Don't forget to invert due OpenGL rendering from Major to Minor (or the opposite)?
    if(mouse_state == SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        this->Rotate(xoffset, -yoffset);
    } else SDL_SetRelativeMouseMode(SDL_FALSE);
}

void Solar::Scene::FreeCamera::ProcessKeyboard()
{
    const Solar::Types::U8* keyboard_state = SDL_GetKeyboardState(NULL);
    WHEN(keyboard_state[SDL_SCANCODE_W], this->Move(Solar::Scene::FreeCameraMovementDirections::FORWARD));
    WHEN(keyboard_state[SDL_SCANCODE_S], this->Move(Solar::Scene::FreeCameraMovementDirections::BACKWARD));
    WHEN(keyboard_state[SDL_SCANCODE_A], this->Move(Solar::Scene::FreeCameraMovementDirections::LEFT));
    WHEN(keyboard_state[SDL_SCANCODE_D], this->Move(Solar::Scene::FreeCameraMovementDirections::RIGHT));
}

void Solar::Scene::FreeCamera::Rotate(Solar::Types::D32 xoff, Solar::Types::D32 yoff)
{
    xoff *= this->sensitivity;
    yoff *= this->sensitivity;
    this->yaw   += xoff;
    this->pitch += yoff;

    // NOTE: here is different from the learnopengl version:
    if(this->pitch > 89.0f) this->pitch = 89.0f;
    if(this->pitch < -89.f) this->pitch = -89.0f;

    // Update the vector here!
    this->UpdateCameraVectors();
}

void Solar::Scene::FreeCamera::Move(Solar::Scene::FreeCameraMovementDirections direction)
{
    Solar::Types::D32 velocity = this->speed;
    switch(direction)
    {
        case Solar::Scene::FreeCameraMovementDirections::FORWARD:
            this->position += this->front * velocity;
            break;
        case Solar::Scene::FreeCameraMovementDirections::BACKWARD:
            this->position -= this->front * velocity;
            break;
        case Solar::Scene::FreeCameraMovementDirections::LEFT:
            this->position -= this->right * velocity;
            break;
        case Solar::Scene::FreeCameraMovementDirections::RIGHT:
            this->position += this->right * velocity;
            break;
    };
}