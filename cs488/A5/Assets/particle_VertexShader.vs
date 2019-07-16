#version 330

out vec2 tex_coords;

in vec3 position;

uniform mat4 Perspective;
uniform mat4 ModelView;

void main()
{
    tex_coords = position.xy;
    vec4 pos = Perspective * ModelView * vec4(position, 1.0);
    gl_Position = pos.xyzw;
}