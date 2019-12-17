#include "Gameobject.h"

Gameobject::Gameobject(btVector3 origin, float mass, btCollisionShape* nshape, glm::vec3 nscale) {
    scale = nscale;
    shape = nshape;
    transform.setIdentity();
    transform.setOrigin(origin);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);
    
    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    rigidbody = new btRigidBody(rbInfo);
}

Gameobject::Gameobject(btTransform otransform, float mass, btCollisionShape* nshape) {
    scale = glm::vec3(1, 1, 1);
    shape = nshape;
    transform = otransform;

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);
    
    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    rigidbody = new btRigidBody(rbInfo);
}