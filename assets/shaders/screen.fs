#version 330 core
out vec4 FragColor;
in vec3 color;

uniform vec3 lightColor;
uniform vec3 blockColor;


void main() {
    float ambientStrength = 1.0;
    vec3 ambient = ambientStrength * lightColor;

    vec4 result = vec4(ambient, 1.0) * vec4(normalize(blockColor), 1.0);
    FragColor = result;
}