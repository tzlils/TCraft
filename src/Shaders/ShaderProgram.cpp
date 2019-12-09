#include "ShaderProgram.h"
#include "../GLAD/glad.h"
#include "../GLM/gtc/type_ptr.hpp"
#include <cstdio>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* vertPath, const char* fragPath) {
    ID = glCreateProgram();
    vertex = new Shader(readfile(vertPath), GL_VERTEX_SHADER);
    fragment = new Shader(readfile(fragPath), GL_FRAGMENT_SHADER);
    vertex->attach(ID);
    fragment->attach(ID);
    glLinkProgram(ID);

    int  success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        printf("Shader Program Link Error: %s\n", infoLog);
    }

    vertex->dispose();
    fragment->dispose();
}

void ShaderProgram::bind() {
    glUseProgram(ID);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}

void ShaderProgram::dispose() {
    glDeleteProgram(ID);
    delete this;
}

void ShaderProgram::setUniform4f(const char* name, float a, float b, float c, float d) {
    int loc = glGetUniformLocation(ID, name);
    glUniform4f(loc, a, b, c, d);
}

void ShaderProgram::setInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setVec3(const char* name, glm::vec3 vec) {
    glUniform3f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z);
}

std::string ShaderProgram::readfile(const char *fileName) {
    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}