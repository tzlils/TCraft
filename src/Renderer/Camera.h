#pragma once
#include "../GLM/glm.hpp"

class Camera {
    public:
        Camera(float fov, float width, float height);
        void update(float delta);
        void rotate(float angle, glm::vec3 axis);
        void resize(float width, float height);
        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 position;
        glm::vec3 direction;
        float yaw;
        float pitch;
    private:
        float fov;
        float width;
        float height;
};