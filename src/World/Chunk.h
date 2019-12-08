#pragma once
#include "Block.h"

class Chunk {
    public:
        Chunk();
        Block*** map;
        bool active;
    private:
        void generateSphere();
};