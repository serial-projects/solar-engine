#version 330 core

uniform uint SE_CurrentColor;

out vec4    fragcolor;  
in vec3     vertcolor;

// NOTE: SE_CurrentColor only packs U8xU8xU8 or RGB color, there is no ALPHA channel:
vec4 SE_GetColorFromCurrentColor()
{
    return vec4(
        float(SE_CurrentColor >> 24u & 255u) / 255,
        float(SE_CurrentColor >> 16u & 255u) / 255,
        float(SE_CurrentColor >>  8u & 255u) / 255,
        float(SE_CurrentColor >>  0u & 255u) / 255
    );
}

void main()
{
    // fragcolor = vec4(vertcolor, 1.0f);
    fragcolor = SE_GetColorFromCurrentColor();
}