#version 330 core

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 normal;

out vec3 Normal;

void main() {
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    Normal = (normal * vec4(in_Normal, 0.0)).xyz;
}