#pragma once
#include "GameObject.h"

class Plane : public GameObject {
    public:
        Plane();
        void generateMesh();
        // void render(ShaderProgram* shader) override;
        int width;
        int height;
        unsigned int EBO;
};