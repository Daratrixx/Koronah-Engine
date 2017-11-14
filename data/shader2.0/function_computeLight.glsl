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
