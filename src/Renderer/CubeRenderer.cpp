#include "CubeRenderer.h"
#include "../GLAD/glad.h"
#include "../GLM/glm.hpp"

CubeRenderer::CubeRenderer(glm::vec3 color, float scale) {
    this->scale = scale;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    float vertices[] = {
        -scale, -scale, -scale, color.r, color.g, color.b,
        scale, -scale, -scale,  color.r, color.g, color.b,
        scale,  scale, -scale,  color.r, color.g, color.b,
        scale,  scale, -scale,  color.r, color.g, color.b,
        -scale,  scale, -scale, color.r, color.g, color.b,
        -scale, -scale, -scale, color.r, color.g, color.b,

        -scale, -scale,  scale, color.r, color.g, color.b,
        scale, -scale,  scale,  color.r, color.g, color.b,
        scale,  scale,  scale,  color.r, color.g, color.b,
        scale,  scale,  scale,  color.r, color.g, color.b,
        -scale,  scale,  scale, color.r, color.g, color.b,
        -scale, -scale,  scale, color.r, color.g, color.b,

        -scale,  scale,  scale, color.r, color.g, color.b,
        -scale,  scale, -scale, color.r, color.g, color.b,
        -scale, -scale, -scale, color.r, color.g, color.b,
        -scale, -scale, -scale, color.r, color.g, color.b,
        -scale, -scale,  scale, color.r, color.g, color.b,
        -scale,  scale,  scale, color.r, color.g, color.b,

        scale,  scale,  scale,  color.r, color.g, color.b,
        scale,  scale, -scale,  color.r, color.g, color.b,
        scale, -scale, -scale,  color.r, color.g, color.b,
        scale, -scale, -scale,  color.r, color.g, color.b,
        scale, -scale,  scale,  color.r, color.g, color.b,
        scale,  scale,  scale,  color.r, color.g, color.b,

        -scale, -scale, -scale, color.r, color.g, color.b,
        scale, -scale, -scale,  color.r, color.g, color.b,
        scale, -scale,  scale,  color.r, color.g, color.b,
        scale, -scale,  scale,  color.r, color.g, color.b,
        -scale, -scale,  scale, color.r, color.g, color.b,
        -scale, -scale, -scale, color.r, color.g, color.b,

        -scale,  scale, -scale, color.r, color.g, color.b,
        scale,  scale, -scale,  color.r, color.g, color.b,
        scale,  scale,  scale,  color.r, color.g, color.b,
        scale,  scale,  scale,  color.r, color.g, color.b,
        -scale,  scale,  scale, color.r, color.g, color.b,
        -scale,  scale, -scale, color.r, color.g, color.b
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0); 
}

void CubeRenderer::bind() {
    glBindVertexArray(VAO);
}