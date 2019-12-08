#include "Application.h"
#include "Shaders/ShaderProgram.h"
#include "Renderer/QuadRenderer.h"
#include "Renderer/CubeRenderer.h"
#include "Renderer/Texture.h"
#include "World/World.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include <stdio.h>
#include <math.h>

Application::Application() {
    
}


void Application::run() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(800, 600, "TCraft", NULL, NULL);
    if(window == NULL) {
        printf("Error");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD");
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    

    ShaderProgram* shader = new ShaderProgram("assets/shaders/screen.vs", "assets/shaders/screen.fs");
    CubeRenderer* cube = new CubeRenderer();
    Texture* texture = new Texture("assets/textures/box.png");
    World* world = new World();
    camera = new Camera(90.0f, 800.0f, 600.0f);

    shader->bind();
    // float timeValue = glfwGetTime();
    // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

    while(!glfwWindowShouldClose(window)) {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;  

        processInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->update(delta_time);

        shader->setMat4("view", camera->view);
        shader->setMat4("projection", camera->projection);

        texture->bind();
        cube->bind();

        for(unsigned int cx = 0; cx < MAP_SIZE; cx++) {
            for(unsigned int cy = 0; cy < MAP_SIZE; cy++) {
                for(unsigned int cz = 0; cz < MAP_SIZE; cz++) {
                    if(!world->map[cx][cy][cz].active) continue;

                    for(unsigned int x = 0; x < CHUNK_SIZE; x++) {
                        for(unsigned int y = 0; y < CHUNK_SIZE; y++) {
                            for(unsigned int z = 0; z < CHUNK_SIZE; z++) {
                                if(!world->map[cx][cy][cz].map[x][y][z].active) continue;
                                glm::mat4 model = glm::mat4(1.0f);
                                model = glm::translate(model, glm::vec3(x+cx, y+cy, z+cz));
                                float angle = 0.0f;
                                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                                shader->setMat4("model", model);

                                glDrawArrays(GL_TRIANGLES, 0, 36);
                            }
                        }
                    }

                }
            }
        }

        // for(unsigned int i = 0; i < 10; i++) {
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, cubePositions[i]);
        //     float angle = 0.0f; 
        //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     shader->setMat4("model", model);

        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::processInput() {
    bool keyExit = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
    bool keyForward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    bool keyBackwards = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    bool keyLeft = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    bool keyRight = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    bool keyFlyUp = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    bool keyFlyDown = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

    bool keyRotateLeft = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    bool keyRotateRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    bool keyRotateUp = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    bool keyRotateDown = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;

    float rotSensitivity = 50.0f;
    float speed = 7.0f;
    speed *= delta_time;

    if(keyExit)
        glfwSetWindowShouldClose(window, true);
    
        if(keyForward) {
        camera->position.z -= speed;
    }   if(keyBackwards) {
        camera->position.z += speed;
    }   if(keyLeft) {
        camera->position.x -= speed;
    }   if(keyRight) {
        camera->position.x += speed;
    }   if(keyFlyUp) {
        camera->position.y -= speed;
    }   if(keyFlyDown) {
        camera->position.y += speed;
    }   if(keyRotateLeft) {
        camera->yaw -= rotSensitivity * delta_time;
    }   if(keyRotateRight) {
        camera->yaw += rotSensitivity * delta_time;
    }   if(keyRotateUp) {
        camera->pitch += rotSensitivity * delta_time;
    }   if(keyRotateDown) {
        camera->pitch -= rotSensitivity * delta_time;
    }
    
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}