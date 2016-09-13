#version 330 core

in float v_opacity[1];
in float v_size[1];
//in int v_textureIndex[1];

//uniform int textureAtlasColumn = 1;
//uniform int textureAtlasRow = 1;

out float f_opacity;
out vec2 f_texCoord;

    layout(points) in;
    layout(triangle_strip, max_vertices = 6) out;

    void main()
    {
        f_opacity = v_opacity[0];
	float size = v_size[0];
        gl_Position = gl_in[0].gl_Position + vec4(-size,-size,0,0);
	f_texCoord = vec2(0,0);
        EmitVertex();
        gl_Position = gl_in[0].gl_Position + vec4(-size,size,0,0);
	f_texCoord = vec2(0,1);
        EmitVertex();
        gl_Position = gl_in[0].gl_Position + vec4(size,size,0,0);
	f_texCoord = vec2(1,1);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(-size,-size,0,0);
	f_texCoord = vec2(0,0);
        EmitVertex();
        gl_Position = gl_in[0].gl_Position + vec4(size,size,0,0);
	f_texCoord = vec2(1,1);
        EmitVertex();
        gl_Position = gl_in[0].gl_Position + vec4(size,-size,0,0);
	f_texCoord = vec2(1,0);
        EmitVertex();
        EndPrimitive();
    }