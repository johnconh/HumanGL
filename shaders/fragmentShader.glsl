#version 330 core

in vec3 fragNormal;

out vec4 fragColor;

uniform vec3 objectColor;

void main() {
    fragColor = vec4(objectColor, 1.0); 
}