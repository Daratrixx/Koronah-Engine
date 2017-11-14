// return q normalized (|q| == 1)
vec4 normalizationQuaternion(vec4 q) {
	return q / sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

// return q*
vec4 conjugationQuaternion(vec4 q) {
	return q * vec4(-1, -1, -1, 1);
}

// return q-1
vec4 inversionQuaternion(vec4 q) {
	return conjugationQuaternion(q) / sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

// return the result of the operation q1 * q2
vec4 multiplicationQuaternion(vec4 q1, vec4 q2) {
	vec4 output;
	output.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
	output.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
	output.z = (q1.w * q2.z) + (q1.x * q2.w) - (q1.y * q2.x) + (q1.z * q2.w);
	output.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
	return output;
}

// return the quaternion corresponding to the position
vec4 positionToQuaternion(vec3 position) {
	return vec4(position, 0);
}

// return the quaternion corresponding to the rotation of angle along the specified axis
vec4 axisAngleToQuaternion(vec3 axis, float angle) {
	float half = angle / 2;
	return vec4(axis.x * sin(half), axis.y * sin(half), axis.z * sin(half), cos(half));
}

// return the cumulated transformation of all three axis considering euler angles logic
vec4 eulerAngleToQuaternion(vec3 eulerAngle) {
	vec4 angleX = axisAngleToQuaternion(vec3(1,0,0), eulerAngle.x);
	vec4 angleY = axisAngleToQuaternion(vec3(0,1,0), eulerAngle.y);
	vec4 angleZ = axisAngleToQuaternion(vec3(0,0,1), eulerAngle.z);
	return axisAngleToQuaternion(eulerAngle.xyz, 1);
}

vec3 transformToQuaternion(vec3 position, vec3 eulerAngle) {
	vec4 eulerQ = eulerAngleToQuaternion(eulerAngle);
	vec4 conjQ = conjugationQuaternion(eulerQ);
	vec4 posQ = positionToQuaternion(position);
	return multiplicationQuaternion(multiplicationQuaternion(euleurQ, posQ), conjQ).xyz;
}

