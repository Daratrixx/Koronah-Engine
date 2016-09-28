#version 330 core

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_Textcoord0;

out vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int unitId = -1;

void main()
{
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    vec4 colorId = vec4(0,0,1,1);
		if(unitId > -1) {
		int r, g;
		r = int(unitId);
		g = int(unitId);
		r = r / 256;
		g = g % 256;
		colorId.x = (r*1.0) / 255.0;
		colorId.y = (g*1.0) / 255.0;
		colorId.z = 0;
	}
    color = colorId;
}