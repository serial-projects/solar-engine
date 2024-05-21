#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertcolor;

// Solar Uniforms are here!
uniform int     SolarTickCounter;
uniform mat4    SolarCurrentRenderingModelMatrix;
uniform mat4    SolarCurrentRenderingViewMatrix;
uniform mat4    SolarCurrentRenderingProjectionMatrix;

void main()
{
    gl_Position = SolarCurrentRenderingProjectionMatrix * SolarCurrentRenderingViewMatrix * SolarCurrentRenderingModelMatrix * vec4(position, 1.0);
    //gl_Position = vec4(position, 1.0f);
    vertcolor = color;
}