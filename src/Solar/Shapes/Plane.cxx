#include "Solar/Shapes/Plane.hxx"
#include "Solar/Utils.hxx"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// This is an basic 2D plane that can be represented on 3D space:
void Solar::Shapes::Plane::Init()
{
    this->LoadModel(
        {
            {0.5f,   0.5f,  0.0f},
            { 0.5f, -0.5f,  0.0f},
            {-0.5f, -0.5f,  0.0f},
            {-0.5f,  0.5f,  0.0f}
        },
        {
            {1.0f,  0.0f,   1.0f},
            {0.0f,  1.0f,   1.0f},
            {0.0f,  0.0f,   1.0f},
            {0.1f,  0.0f,   1.0f}
        },
        {},
        { 0, 1, 3, 1, 2, 3 }
    );
}

void Solar::Shapes::Plane::Destroy()
{
    // TODO: unallocate the model from the GPU memory!
    this->UnloadModel();
}