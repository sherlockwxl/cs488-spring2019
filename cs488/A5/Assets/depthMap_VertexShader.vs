#version 330
in vec3 position;

uniform mat4 lightView;
uniform mat4 lightProjection;

void main()
{
    gl_Position = lightProjection * lightView * vec4(position, 1.0);
} 