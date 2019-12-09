#pragma once
#include "../GLM/glm.hpp"

class Transform {
    public:
        Transform();
        Transform* parent;
        glm::vec3 rotation;
        glm::vec3 position;
};