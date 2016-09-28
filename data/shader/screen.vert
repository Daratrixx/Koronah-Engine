#version 330 core
in vec2 in_Position;
in vec2 in_Texture;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(in_Position.x, in_Position.y, 0.0f, 1.0f); 
    TexCoords = in_Texture;
}  