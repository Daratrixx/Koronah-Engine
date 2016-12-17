#version 330 core

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int lightCount = 0;
uniform int hasNormal = 0;
uniform float lightSource[96];

out vec2 coordTexture;
//out vec3 enlightmentColor;

vec4 computeLight(vec3 position, vec3 color, vec3 vertexPosition, vec3 vertexNormal);

void main() {
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    vec3 vertexPosition = (model * vec4(in_Vertex, 1.0)).xyz;
    vec3 vertexNormal = (transpose(inverse(model)) * vec4(in_Normal, 1.0)).xyz;
	
	/*enlightmentColor = vec3(1, 1, 1);
    if(lightCount > 0) {
		enlightmentColor = vec3(1, 1, 1);
		vec4 computedLight[16];
		for(int i=0; i<lightCount; i++) {
			vec3 lightPosition = vec3(lightSource[i * 6],lightSource[i * 6 + 1],lightSource[i * 6 + 2]);
			vec3 lightColor = vec3(lightSource[i * 6 + 3],lightSource[i * 6 + 4],lightSource[i * 6 + 5]);
			computedLight[i] = computeLight(lightPosition, lightColor, vertexPosition, vertexNormal);
			enlightmentColor += vec3(computedLight[i].x, computedLight[i].y, computedLight[i].z) * computedLight[i].w;
		}
		enlightmentColor = enlightmentColor;
    } else {
        vec4 gen = computeLight(vec3(0,0,0), vec3(-1,-1,-1), vertexPosition, vertexNormal);
        enlightmentColor = vec3(gen.x, gen.y, gen.z) * gen.w;
    }*/
    coordTexture = in_TexCoord0;
}

vec4 computeLight(vec3 position, vec3 color, vec3 vertexPosition, vec3 vertexNormal) {
	vec3 distanceVec = position - vertexPosition;
	vec3 lightDirection = normalize(distanceVec);
	int linear = 0;
	if(color.x<0) {
		color.x = -color.x;
		linear = linear + 1;
	}
	if(color.y<0) {
		color.y = -color.y;
		linear = linear + 1;
	}
	if(color.z<0) {
		color.z = -color.z;
		linear = linear + 1;
	}

	// compute distance ratio
	float distance = length(distanceVec);
	float distanceRatio = 1;
	if(linear == 0)
		distanceRatio = 1 / (distance * distance);
		
	// compute normal dot reduction factor
	float dotProduct = 1;
	if(hasNormal == 1)
		dotProduct = max(dot(vertexNormal,lightDirection), 0.05);
		
	// finale force
	float lightForce = dotProduct * distanceRatio;

	return vec4(color, lightForce);
}
