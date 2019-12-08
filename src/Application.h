#pragma once
#include "GLAD/glad.h"
#include "Renderer/Camera.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

class Application {
    public:
        Application();
        void run();
        float getDelta();
    private:
        GLFWwindow* window;
        float last_frame;
        float delta_time;
        void processInput();
        void render();
        Camera* camera;
};

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);