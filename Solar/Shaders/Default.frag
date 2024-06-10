#version 330 core

uniform int SolarTickCounter;
out vec4    fragcolor;  
in vec3     vertcolor;
  
void main()
{
    fragcolor = vec4(vertcolor, 1.0f);
}