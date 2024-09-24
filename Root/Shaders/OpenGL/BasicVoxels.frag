#version 330 core

uniform sampler2D   CurrentTexture;

in  vec2 current_texture_map;
in  vec3 current_normals;
in  vec3 current_fragment_position;

out vec4 fragment_color;

vec4 ProgatorUnpackColorRGBA8(uint color)
{
    return vec4(
        float((color & 4278190080u)   >> 24u) / 255,
        float((color & 16711680u)     >> 16u) / 255,
        float((color & 65280u)        >>  8u) / 255,
        float((color & 255u)          >>  0u) / 255
    );
}

const vec3 light_position   = vec3(125.0f, -125.0f, 256.0f);
const vec3 light_color      = vec3(1.0f, 1.0f, 1.0f);

void main()
{
    /*
     * When the texture has an alpha color less than 0.1, then do not draw.
     */

    
    //const float ambient_light_strength = 0.1;
    //vec3 texture_surface = texture(CurrentTexture, current_texture_map).rgb;
    //vec3 ambient = ambient_light_strength * light_color;

    /* diffuse lightning: */
    //vec3 normalized = normalize(current_normals);
    //vec3 light_direction = normalize(light_position - current_fragment_position);
    
    //float diffuse_amount = max(dot(normalized, light_direction), 0.0f);
    //vec3 diffuse_light = diffuse_amount * light_color;

    /* apply ambient + diffusion: */
    //vec3 light = (ambient + diffuse_light) * texture_surface;

    /* pass to the opengl: */
    //fragment_color = vec4(light, 1.0f);
    

    fragment_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
} 