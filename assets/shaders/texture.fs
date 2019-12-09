#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 lightColor;


void main() {
    float ambientStrength = 1.0;
    vec3 ambient = ambientStrength * lightColor;

    vec4 textured = texture(ourTexture, TexCoord);
    vec4 result = vec4(ambient, 1.0) * textured;
    FragColor = result;
}