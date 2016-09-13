#version 330 core

in vec4 v_Color[1];
in vec2 v_Size[1];

out vec4 f_color;
out vec2 f_texCoord;

layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

void main()
{
	f_color = v_Color[0];
	vec2 size = v_Size[0];
	gl_Position = gl_in[0].gl_Position + vec4(0,0,0,0);
	f_texCoord = vec2(0,0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0,size.y,0,0);
	f_texCoord = vec2(0,1);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(size.x,size.y,0,0);
	f_texCoord = vec2(1,1);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0,0,0,0);
	f_texCoord = vec2(0,0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(size.x,size.y,0,0);
	f_texCoord = vec2(1,1);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(size.x,0,0,0);
	f_texCoord = vec2(1,0);
	EmitVertex();
	EndPrimitive();
}