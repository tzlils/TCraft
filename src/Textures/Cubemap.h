#include <iostream>
#include <vector>

class Cubemap {
    public:
        Cubemap(std::vector<std::string> faces);
        void bind();
        void unbind();
    private:
        unsigned int texture;
};