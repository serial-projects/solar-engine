#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coord;
layout (location = 2) in vec3 normals;

uniform mat4 ProgatorProjectionMatrix;
uniform mat4 ProgatorViewMatrix;
uniform mat4 ProgatorModelMatrix;

out vec2 current_texture_map;
out vec3 current_normals;
out vec3 current_fragment_position;

void main()
{
    /* 
     * NOTE: since we rendering in 3D, we don't need the Z axis.
     * so we discard it by using 0.0f on Z index.
     */
    gl_Position = ProgatorProjectionMatrix * ProgatorViewMatrix * ProgatorModelMatrix * vec4(position, 1.0f);

    /* get the fragment position */
    current_fragment_position = vec3(ProgatorModelMatrix * vec4(position, 1.0f));

    /* pass forward this information: */
    current_texture_map     = texture_coord;
    current_normals         = normals;
}