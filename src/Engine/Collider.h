#include "Rigidbody.h"

class Collider {
    Rigidbody* attachedRigidbody;
    glm::vec3 closestPoint(glm::vec3 position);
};