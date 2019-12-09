#include "GameObject.h"
#include "../GLM/glm.hpp"

class Voxel : public GameObject {
    public:
        Voxel();
        void generateMesh();
};