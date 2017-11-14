#version 330 core

in vec3 in_Vertex;
in vec3 in_Normal;
in vec3 in_Color;
in vec2 in_TexCoord0;
in vec2 in_TexCoord1;
in vec2 in_TexCoord2;
in vec2 in_TexCoord3;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int textureCount = 0;

out vec2 TexCoord0;
out vec2 TexCoord1;
out vec2 TexCoord2;
out vec2 TexCoord3;