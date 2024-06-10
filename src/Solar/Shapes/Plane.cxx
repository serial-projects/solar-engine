#include "Solar/Shapes/Plane.hxx"
#include "Solar/Utils.hxx"
#include "Solar/GL.hxx"

// This is an basic 2D plane that can be represented on 3D space:
void Solar::Shapes::Plane::Init()
{
    this->LoadMesh(
        {
            {0.5f,   0.5f,  0.0f},
            { 0.5f, -0.5f,  0.0f},
            {-0.5f, -0.5f,  0.0f},
            {-0.5f,  0.5f,  0.0f}
        },
        {},
        {},
        { 0, 1, 3, 1, 2, 3 }
    );
}

void Solar::Shapes::Plane::Destroy()
{
    // TODO: unallocate the model from the GPU memory!
    this->UnloadMesh();
}