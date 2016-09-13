#version 330 core

in vec2 coordTexture;
//in vec2 coordGlow;
//in vec2 coordHeight;
in vec3 enlightmentColor;

uniform sampler2D texture;

out vec4 out_Color;

void main()
{
    vec4 tex=(texture(texture, coordTexture)) * vec4(enlightmentColor,1);
    if(tex.w<0.1)
        discard;
    out_Color = tex;
}
