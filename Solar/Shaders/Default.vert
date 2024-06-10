#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 texture_map;

out vec3 vertcolor;

uniform int     SE_TickCounter;
uniform mat4    SE_MeshMatrix;
uniform mat4    SE_ViewMatrix;
uniform mat4    SE_ProjectionMatrix;

void main()
{
    // Solve for pespective:
    gl_Position = SE_ProjectionMatrix * SE_ViewMatrix * SE_MeshMatrix * vec4(position, 1.0);
    vertcolor = color;
}