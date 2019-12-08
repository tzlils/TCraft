#pragma once
#include <string>

class Shader {
    public:
        Shader();
        Shader(std::string code, int type);
        void attach(int program);
        void dispose();
    private:
        unsigned int ID;
};