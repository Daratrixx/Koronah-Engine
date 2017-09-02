#version 330 core

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_TexCoord0; // color1
in vec2 in_TexCoord1; // color2
in vec2 in_TexCoord2; // 
in vec2 in_TexCoord3;
in int in_BoneUsage;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 bones[10];
uniform int renderMode = 1; // 1 TEXTURE | 2 NORMAL | 3 HALO

out vec2 coordTexture;

mat4 computeBones() {
    mat4 out;
    int bit = 1;
    for(int i = 0; i < 10; i++) {
        if(in_BoneUsage & bit != 0)
	    out = out * bones[i];
        bit = bit * 2;
    }
    return out;

}

void main() {
    gl_Position = projection * view * model * computeBones() * vec4(in_Vertex, 1.0);
    vec3 vertexPosition = (model * vec4(in_Vertex, 1.0)).xyz;
    vec3 vertexNormal = (transpose(inverse(model)) * vec4(in_Normal, 1.0)).xyz;
    coordTexture = in_TexCoord0;
}