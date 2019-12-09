#pragma once
#include "GameObject.h"
#include "Transform.h"

class Component {
    public:
        Component();
        GameObject* gameObject;
        Transform* transform;
};