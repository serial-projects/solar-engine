#version 330 core

uniform int SE_CurrentColor;

out vec4    fragcolor;  
in vec3     vertcolor;

// NOTE: SE_CurrentColor only packs U8xU8xU8 or RGB color, there is no ALPHA channel:
vec4 SE_GetColorFromCurrentColor()
{
    return vec4(
        ( (SE_CurrentColor >> 24) & 0xFF ),
        ( (SE_CurrentColor >> 16) & 0xFF ),
        ( (SE_CurrentColor >>  8) & 0xFF ),
        ( (SE_CurrentColor >>  0) & 0xFF )
    );
}

void main()
{
    // fragcolor = vec4(vertcolor, 1.0f);
    fragcolor = SE_GetColorFromCurrentColor();
}