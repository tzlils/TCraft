#include "Application.h"
#include "Shaders/ShaderProgram.h"
#include "Renderer/QuadRenderer.h"
#include "Renderer/CubeRenderer.h"
#include "Textures/Texture.h"
#include "Textures/Cubemap.h"
#include "World/World.h"
// #include "Engine/Voxel.h"
// #include "Engine/Plane.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "bullet/btBulletDynamicsCommon.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

std::vector<std::string> faces {
    "assets/textures/skybox/right.jpg",
    "assets/textures/skybox/left.jpg",
    "assets/textures/skybox/top.jpg",
    "assets/textures/skybox/bottom.jpg",
    "assets/textures/skybox/front.jpg",
    "assets/textures/skybox/back.jpg"
};

std::vector<std::string> grassfaces {
    "assets/textures/grass_side.jpg",
    "assets/textures/grass_side.jpg",
    "assets/textures/grass_side.jpg",
    "assets/textures/grass_side.jpg",
    "assets/textures/grass_side.jpg",
    "assets/textures/grass_side.jpg"
};

int paused;

Application::Application() {
    
}

void Application::initGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(1920, 1080, "TCraft", NULL, NULL);
    if(window == NULL) {
        printf("Error");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD");
    }
}

void Application::initBullet() {
}

void Application::run() {
    initGL();
    // initBullet();

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -.1f, 0));

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 1920, 1080);
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    ShaderProgram* shader = new ShaderProgram("assets/shaders/screen.vs", "assets/shaders/screen.fs");
    ShaderProgram* skybox = new ShaderProgram("assets/shaders/skybox.vs", "assets/shaders/skybox.fs");

    CubeRenderer* cube = new CubeRenderer(glm::vec3(1.0, 1.0, 1.0), 1.0f);
    QuadRenderer* quad = new QuadRenderer();
    Texture* texture = new Texture("assets/textures/grass.jpg");

    Cubemap* skyboxCubemap = new Cubemap(faces);
    Cubemap* grassCubemap = new Cubemap(grassfaces);

    camera = new Camera(90.0f, 800.0f, 600.0f);

    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -1, 0));
    btScalar mass(0.);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        groundShape->calculateLocalInertia(mass, localInertia);
    
    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
    btRigidBody* groundBody = new btRigidBody(rbInfo);

    //add the body to the dynamics world
    // dynamicsWorld->addRigidBody(groundBody);


    btTransform startTransform;
    startTransform.setIdentity();
    mass = 1.f;

    int ARRAY_SIZE_X = 6;
    int ARRAY_SIZE_Y = 6;
    int ARRAY_SIZE_Z = 6;
    float start_x = 0 - ARRAY_SIZE_X / 2;
    float start_y = 0;
    float start_z = 0 - ARRAY_SIZE_Z / 2;
    for (int x = 0; x < ARRAY_SIZE_X; x++) {
        for (int y = 0; y < ARRAY_SIZE_Y; y++) {
            for (int z = 0; z < ARRAY_SIZE_Z; z++) {
                startTransform.setOrigin(.5 * btVector3(
                                            btScalar(2.0 * x + start_x),
                                            btScalar(2.0 * z + start_z),
                                            btScalar(20 + 2.0 * y + start_y)));
                btCollisionShape* colShape = new btBoxShape(btVector3(btScalar(2.), btScalar(2.), btScalar(2.)));
                bool isDynamic = (mass != 0.f);
                btVector3 localInertia(0, 0, 0);

                if (isDynamic)
                    colShape->calculateLocalInertia(mass, localInertia);

                //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
                btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(btScalar(mass), myMotionState, colShape, localInertia);
                btRigidBody* body = new btRigidBody(rbInfo);
                // body->setFriction(1.f);
                // body->setRollingFriction(.1);
                // body->setSpinningFriction(0.1);
                // body->setAnisotropicFriction(colShape->getAnisotropicRollingFrictionDirection(), btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
                dynamicsWorld->addRigidBody(body);
            }
        }
        
    }
    

    // float timeValue = glfwGetTime();
    // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    // plane->width = 20;
    // plane->height= 20;
    // plane->transform->position = glm::vec3(-5.0, -5.0, -5.0);
    // plane->generateMesh();
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    while(!glfwWindowShouldClose(window)) {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;  

        processInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->bind();
        camera->update(delta_time);

        shader->setMat4("view", camera->view);
        shader->setMat4("projection", camera->projection);
        shader->setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));

        // grassCubemap->bind();
        // plane->transform->rotation.x = M_PI_2;
        // plane->render(shader);

        // groundBody->getWorldTransform().getRotation().setZ(M_PI_2);

        // quad->bind();
        texture->bind();
        cube->bind();
        dynamicsWorld->stepSimulation(delta_time * paused);
        for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState()) {
				body->getMotionState()->getWorldTransform(trans);
			}
			else {
				trans = obj->getWorldTransform();
			}
            // trans.setRotation(btQuaternion(btVector3(0, 1, 0), xangle));
            
			// printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(1, 1, 1));
            model = glm::rotate(model, trans.getRotation().getX(), glm::vec3(1, 0, 0));
            model = glm::rotate(model, trans.getRotation().getY(), glm::vec3(0, 1, 0));
            model = glm::rotate(model, trans.getRotation().getZ(), glm::vec3(0, 0, 1));
            model = glm::translate(model, glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
            shader->setVec3("blockColor", glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
            shader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
        }

        // for(unsigned int cx = 0; cx < MAP_SIZE; cx++) {
        //     for(unsigned int cy = 0; cy < MAP_SIZE; cy++) {
        //         for(unsigned int cz = 0; cz < MAP_SIZE; cz++) {
        //             if(!world->map[cx][cy][cz].active) continue;
        //             for(unsigned int x = 0; x < CHUNK_SIZE; x++) {
        //                for(unsigned int y = 0; y < CHUNK_SIZE; y++) {
        //                     for(unsigned int z = 0; z < CHUNK_SIZE; z++) {
        //                         if(!world->map[cx][cy][cz].map[x][y][z].active) continue;
        //                         model = glm::translate(model, glm::vec3(x + cx*CHUNK_SIZE, y + cy*CHUNK_SIZE, z + cz*CHUNK_SIZE));
        //                         shader->setMat4("model", model);
        //                         shader->setVec3("blockColor", glm::vec3(x, y, z));

        //                         glDrawArrays(GL_TRIANGLES, 0, 36);
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }

        // glDepthFunc(GL_LEQUAL);
        // skybox->bind();
        // skybox->setMat4("view", glm::mat4(glm::mat3(camera->view)));
        // skybox->setMat4("projection", camera->projection);

        // glBindVertexArray(skyboxVAO);
        // skyboxCubemap->bind();
        // glActiveTexture(GL_TEXTURE0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        // glBindVertexArray(0);
        // glDepthFunc(GL_LESS);

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

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// glm::vec2 intersectBox(glm::vec3 origin, glm::vec3 dir, GameObject* b) {
//   glm::vec3 tMin = (b->min - origin) / dir;
//   glm::vec3 tMax = (b->max - origin) / dir;
//   glm::vec3 t1 = glm::min(tMin, tMax);
//   glm::vec3 t2 = glm::max(tMin, tMax);
//   float tNear = glm::max(glm::max(t1.x, t1.y), t1.z);
//   float tFar = glm::min(glm::min(t2.x, t2.y), t2.z);
  
//   return glm::vec2(tNear, tFar);
// }

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

    bool keyRotatePlane = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;

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
    }   if(keyRotatePlane) {
        paused = !paused;
    }
    
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}