#version 330 core


//uniform int textureAtlasColumn = 1;
//uniform int textureAtlasRow = 1;

in float f_opacity;
in vec2 f_texCoord;

uniform sampler2D texture;

out vec4 out_Color;

void main()
{
    vec4 tex=(texture(texture, f_texCoord)) * vec4(1,1,1,f_opacity);
    if(tex.w<0.1)discard;
    out_Color = tex;
}
