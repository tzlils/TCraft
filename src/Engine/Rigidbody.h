#include "../GLM/glm.hpp"
#include "../GLM/gtc/quaternion.hpp"

class Rigidbody {
    public:
        Rigidbody();
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 velocity;

        float angularVelocity;
};