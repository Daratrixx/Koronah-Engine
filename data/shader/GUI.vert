#version 330 core

in vec2 in_Vertex;
in vec2 in_Size;
in vec4 in_Color;

out vec2 v_Size;
out vec4 v_Color;

void main()
{
    gl_Position = vec4(in_Vertex, 1, 1);
    v_Size = vec2(in_Size.x,in_Size.y);
    v_Color = in_Color;
}  