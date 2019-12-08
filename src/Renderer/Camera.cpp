#include "Camera.h"
#include "../GLM/glm.hpp"
#include "../GLM/gtc/matrix_transform.hpp"
#include "../GLM/gtc/type_ptr.hpp"

Camera::Camera(float fov, float width, float height) {
    this->fov = fov;
    this->width = width;
    this->height = height;

    projection = glm::mat4(1.0f);
    view = glm::mat4(1.0f);


    position   = glm::vec3(0.0f, 0.0f,  3.0f);
    pitch = 0.0f;
    yaw = 0.0f;


    projection = glm::perspective(glm::radians(fov), (float)width/(float)height, 0.1f, 100.0f);
}

void Camera::update(float delta) {
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    view = glm::lookAt(position, position + glm::normalize(front), cameraUp);
}