#include "Shader.h"
#include "../GLAD/glad.h"

Shader::Shader() {
 
}

Shader::Shader(std::string code, int type) {
    ID = glCreateShader(type);
    const char* c = code.c_str();
    glShaderSource(ID, 1, &c, NULL);
    glCompileShader(ID);

    int  success;
    char infoLog[512];
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        if(type == GL_FRAGMENT_SHADER) {
            printf("Fragment Shader Compilation Error: %s", infoLog);
        } else if(type == GL_VERTEX_SHADER) {
            printf("Vertex Shader Compilation Error: %s", infoLog);
        }
    }
}

void Shader::attach(int program) {
    glAttachShader(program, ID);
}

void Shader::dispose() {
    glDeleteShader(ID);
    delete this;
};