#version 330 core

in vec3 in_Vertex;
in float in_Opacity;
in float in_Size;
in int in_TextureIndex;

uniform mat4 projection;
uniform mat4 view;

out float v_opacity;
out float v_size;
//out int v_textureIndex;

void main()
{
	gl_Position = projection * view * vec4(in_Vertex, 1);
	v_opacity = in_Opacity;
	v_size = in_Size;
}
