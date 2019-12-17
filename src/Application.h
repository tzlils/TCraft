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
        void initGL();
        void initBullet();
        GLFWwindow* window;
        float last_frame;
        float delta_time;
        void processInput();
        // void checkRaycasting(Camera* camera, std::vector<GameObject*> objects);
        void render();
        Camera* camera;
};

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);