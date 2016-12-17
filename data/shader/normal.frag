#version 330 core

in vec3 Normal;

out vec4 out_Color;

void main() {
    vec3 n = normalize(Normal);
    out_Color = vec4(n, 0.5);
}
