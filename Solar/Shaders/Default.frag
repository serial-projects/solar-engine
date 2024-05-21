#version 330 core

uniform int SolarTickCounter;
out vec4    fragcolor;  
in vec3     vertcolor;
  
void main()
{
    //fragcolor = vec4(
        //((sin(SolarTickCounter / (60 / 2)) * 256) + vertcolor.x) / 256,
        //((cos(SolarTickCounter / (60 / 4)) * 128) + vertcolor.y) / 256,
        //((sin(SolarTickCounter / (60 / 8)) *  64) + vertcolor.z) / 256,
        //1.0
    //);

    // fragcolor = vec4(
    //     (sin(SolarTickCounter / 120)     * (vertcolor.x * 256)) / 256,
    //     (sin(SolarTickCounter / 120)     * (vertcolor.y * 256)) / 256,
    //     (sin(SolarTickCounter / 120)     * (vertcolor.z * 256)) / 256,
    //     1.0f
    // );

    fragcolor = vec4(vertcolor, 1.0f);
}