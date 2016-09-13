#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D image;
const int texelSize = 3;
const int iteration = 5;
const float[10] weight = float[](0.8,0.4,0.2,0.1,0.05,0.025,0.0125,0.0075,0.005,0.0025);


void main()
{             
     vec2 tex_offset = textureSize(image, 0); // gets size of single texel
     tex_offset = vec2(texelSize/tex_offset.x,texelSize/tex_offset.y); // gets size of single texel
     //vec2 tex_offset = vec2(0.0016,0.0012); // gets size of single texel
     vec3 result = texture(image, TexCoords).rgb;
         for(int i = 1; i < iteration; ++i)
         {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            for(int j = 1; j < i; ++j)
            {
                result += texture(image, TexCoords + vec2(tex_offset.x * i, tex_offset.y * j)).rgb * weight[j];
                result += texture(image, TexCoords + vec2(-tex_offset.x * i, tex_offset.y * j)).rgb * weight[j];
                result += texture(image, TexCoords + vec2(tex_offset.x * i, -tex_offset.y * j)).rgb * weight[j];
                result += texture(image, TexCoords + vec2(-tex_offset.x * i, -tex_offset.y * j)).rgb * weight[j];
                result += texture(image, TexCoords + vec2(0, -tex_offset.y * j)).rgb * weight[j];
                result += texture(image, TexCoords + vec2(0, -tex_offset.y * j)).rgb * weight[j];
            }
         }
     FragColor = vec4(result, 1.0);
     FragColor.w = (FragColor.x+FragColor.y+FragColor.z)/3;
}

/*#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

const float offset = 1.0 / 500; 
const float ratio = 8; 

void main()
{
    //float offset = 1.0 / length(textureSize(screenTexture, 0)); 
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right
    );

    float kernel[9] = float[](
         1/ratio,  2/ratio,  1/ratio,
         2/ratio,  4/ratio,  2/ratio,
         1/ratio,  2/ratio,  1/ratio
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    color = vec4(col,1);
    color.w = (color.x+color.y+color.z)/3;
}*/