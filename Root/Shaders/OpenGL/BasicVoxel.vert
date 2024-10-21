#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coord;
layout (location = 2) in vec3 normals;

uniform mat4 SolarProjectionMatrix;
uniform mat4 SolarViewMatrix;
uniform mat4 SolarModelMatrix;
uniform vec3 SolarCurrentVoxelPosition;

out vec2 current_texture_map;
out vec3 current_normals;
out vec3 current_fragment_position;

void main()
{
    gl_Position = SolarProjectionMatrix * SolarViewMatrix * SolarModelMatrix * vec4(position, 1.0f);

    /* get the fragment position */
    current_fragment_position = vec3(SolarModelMatrix * vec4(position, 1.0f));

    /* pass forward this information: */
    current_texture_map     = texture_coord;
    current_normals         = normals;
}