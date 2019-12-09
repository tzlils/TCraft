#pragma once
#define CHUNK_SIZE 4
#define MAP_SIZE 2
#include "Chunk.h"

class World {
    public:
        World();  
        Chunk*** map;
    private:
        void generateChunks();
};