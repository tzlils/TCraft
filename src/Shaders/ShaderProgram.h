#pragma once
#include "Shader.h"
#include "../GLM/glm.hpp"

class ShaderProgram {
    public:
        ShaderProgram();
        ShaderProgram(const char* vertPath, const char* fragPath);
        void dispose();
        void bind();
        void unbind();
        void setInt(const char* name, int value);
        void setUniform4f(const char* name, float a, float b, float c, float d);
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void setVec3(const char* name, glm::vec3 vec);
    private:
        std::string readfile(const char* path);
        Shader* vertex;
        Shader* fragment;
        unsigned int ID;
};