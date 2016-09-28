#version 330 core

in vec2 in_Position;

void main()
{
    gl_Position = vec4(in_Position, 1, 1);
}