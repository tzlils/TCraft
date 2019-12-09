#include "Plane.h"
#include "GameObject.h"
#include "../GLAD/glad.h"
#include "../GLM/glm.hpp"

Plane::Plane() {
    generateMesh();
}

void Plane::generateMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /*
        0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    */

    glBindVertexArray(VAO);
    float scale = 0.05f;
    glm::vec3 color = glm::vec3(0.0, 1.0, 0.0);
    float vertices[] = {
        width,  height, 0.0f,   1.0f, 0.0f, 0.0f,   // top right
        width,  -height, 0.0f,   0.0f, 1.0f, 0.0f,   // bottom right
        -width, -height, 0.0f,   0.0f, 0.0f, 1.0f,   // bottom left
        -width,  height, 0.0f,   1.0f, 1.0f, 0.0f,    // top left 
    };


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0); 
}

// void Plane::render(ShaderProgram* shader) {
//     glm::mat4 model = glm::mat4(1.0f);
//     model = glm::translate(model, transform->position);
//     model = glm::rotate(model, transform->rotation.x, glm::vec3(1.0, 0.0, 0.0));
//     model = glm::rotate(model, transform->rotation.y, glm::vec3(0.0, 1.0, 0.0));
//     model = glm::rotate(model, transform->rotation.z, glm::vec3(0.0, 0.0, 1.0));
//     transform->rotation = glm::vec3();
//     shader->setMat4("model", model);

//     glBindVertexArray(VBO);
//     glDrawArrays(GL_TRIANGLES, 0, 12);
// }