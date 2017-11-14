@data/shader/header_baseFragment.glsl

@data/shader/function_getColorTexture0.glsl
@data/shader/function_getColorTexture1.glsl
@data/shader/function_getColorTexture2.glsl
@data/shader/function_getColorTexture3.glsl


void main() {
    //vec4 tex=(texture(texture, coordTexture)) * vec4(enlightmentColor,1);
    vec4 tex=(texture(texture, coordTexture)) * vec4(modelColor,1);
    if(tex.w<0.1)
        discard;
    out_Color = tex;
}
