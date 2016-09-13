#version 330 core
in vec4 f_color;
in vec2 f_texCoord;

out vec4 color;

uniform int hasTexture = 0;
uniform sampler2D textureData;

void main()
{    
    vec4 sampled;
    if(hasTexture != 0)
        sampled = f_color * texture(textureData, f_texCoord);
    else
        sampled = f_color;
    if(sampled.w < 0.1)
        discard;
    color = sampled;
}
