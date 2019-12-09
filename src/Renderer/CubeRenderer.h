#pragma once
#include "../GLM/glm.hpp"

class CubeRenderer {
    public:
        CubeRenderer(glm::vec3 color, float scale);
        void bind();
        float scale;
    private:
        unsigned int VAO;
        unsigned int VBO;
};