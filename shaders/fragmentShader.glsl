#version 330 core

in vec3 fragNormal;

out vec4 fragColor;

void main() {
    fragColor = vec4(abs(fragNormal), 1.0); 
}