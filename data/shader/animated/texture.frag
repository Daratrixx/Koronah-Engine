#version 330 core

in vec2 coordTexture;

uniform sampler2D Tex[4];
uniform vec3 modelColor = vec3(1, 1, 1);
uniform int renderMode = 1; // 1 TEXTURE | 2 NORMAL | 3 HALO
uniform int in_TexUsage;


out vec4 out_Color;

void main() {
    vec4 tex = vec4(modelColor,1);

    int bit = 1;
    for(int i = 0; i < 10; i++) {
        if(in_TexUsage & bit != 0)
	    out = out * Tex[i];
        bit = bit * 2;
    }
    (texture(Tex0, coordTexture)) * ;
    if(tex.w<0.1)
        discard;
    out_Color = tex;
}
