#pragma once
#define CHUNK_SIZE 16
#define MAP_SIZE 1
#include "Chunk.h"

class World {
    public:
        World();  
        Chunk*** map;
    private:
        void generateChunks();
};