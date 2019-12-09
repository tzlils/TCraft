#pragma once
#include "Transform.h"
#include "Collider.h"
#include "../Shaders/ShaderProgram.h"

class GameObject {
    public:
        GameObject();
        Transform* transform;
        Collider* collider;
        unsigned int VAO;
        unsigned int VBO;
        void render(ShaderProgram* shader);
        void generateMesh();
};