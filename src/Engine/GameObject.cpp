#include "GameObject.h"
#include "Transform.h"
#include "../Shaders/ShaderProgram.h"
#include "../GLAD/glad.h"
#include "../GLM/gtc/quaternion.hpp"

GameObject::GameObject() {
    transform = new Transform();
}

void GameObject::render(ShaderProgram* shader) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transform->position);
    model = glm::rotate(model, transform->rotation.x, glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, transform->rotation.y, glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, transform->rotation.z, glm::vec3(0.0, 0.0, 1.0));
    transform->rotation = glm::vec3();
    shader->setMat4("model", model);

    glBindVertexArray(VBO);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

