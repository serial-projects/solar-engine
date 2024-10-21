#version 330 core

uniform sampler2D   CurrentTexture;
uniform vec3        SolarCurrentVoxelPosition;
uniform vec3        SolarWorldBasicSunPosition;
uniform vec3        SolarCameraPosition;

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

vec3 SolarRootSceneLight            = SolarWorldBasicSunPosition;
vec3 SolarRootSceneLightColor       = vec3(1.0f, 0.5f, 0.3f);

vec4 PointLight()
{
    /* Set the position: */
    vec3    current_position    = current_fragment_position;

    /* takes the current parameters and calculate point light for the scene: */
    vec3    light_vector        = SolarRootSceneLight - current_position;
    float   light_distance      = length(light_vector);
    
    /* begin to apply the quadratic and linear terms: */
    float   quad_term           = 10.0f;
    float   line_term           = 4.0f;
    float   cons_term           = 1.0f;
    
    /* apply 1/(a * (dist) ^ 2 + b * dist + c): */
    float   atten               = 1 / ( (quad_term * light_distance * light_distance) + (line_term * light_distance) + cons_term );

    /* after everything, consider the: ambient lighting, difuse light and specular: */
    float   ambient             = 0.25f;

    vec3    normal              = normalize(current_normals);
    vec3    light_direction     = normalize(light_vector);
    float   diffuse             = max(dot(normal, light_direction), 0.0f);
    
    float   specular_strength   = 0.25f;
    vec3    view_direction      = normalize(SolarCameraPosition - current_position);
    vec3    reflection_direction= reflect(-light_direction, normal); /* opposite to the view: */
    float   specular_amount     = pow( max( dot(view_direction, reflection_direction), 0.0f ), 4);
    float   specular            = specular_amount * specular_strength;

    return vec4(texture(CurrentTexture, current_texture_map).rgb * SolarRootSceneLightColor * (diffuse + ambient + atten + specular), 1.0f);
}

void main()
{
    fragment_color = PointLight();
} 