#version 330 core

in vec2 TexCoord0;
in vec2 TexCoord1;
in vec2 TexCoord2;
in vec2 TexCoord3;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform vec3 modelColor = vec3(1,1,1);

out vec4 out_Color;