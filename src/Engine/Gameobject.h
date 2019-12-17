#include "../GLM/glm.hpp"
#include "bullet/btBulletDynamicsCommon.h"

class Gameobject {
    public:
        Gameobject(btVector3 origin, float mass, btCollisionShape* shape, glm::vec3 scale);
        Gameobject(btTransform transform, float mass, btCollisionShape* shape);
        glm::vec3 scale;
        glm::vec3 color;

        btRigidBody* rigidbody;
        btCollisionShape* shape;
        btTransform transform;
};