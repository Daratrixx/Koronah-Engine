@data/shader/header_baseVertex.glsl

void main() {
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    vec3 vertexPosition = (model * vec4(in_Vertex, 1.0)).xyz;
	
	// send texture coordinates
	if(textureCount>0)
    TexCoord0 = in_TexCoord0;
	if(textureCount>1)
    TexCoord1 = in_TexCoord1;
	if(textureCount>2)
    TexCoord2 = in_TexCoord2;
	if(textureCount>3)
    TexCoord3 = in_TexCoord3;
}
