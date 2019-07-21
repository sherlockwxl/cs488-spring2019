#version 330


in vec3 position;

uniform mat4 translation;

void main()
{
    vec4 pos =  translation * vec4(position,  1.0);
    gl_Position = pos.xyzw;
}