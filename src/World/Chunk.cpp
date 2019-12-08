#include "World.h"
#include "Chunk.h"
#include <stdio.h>
#include <math.h>

Chunk::Chunk() {
    active = false;
    generateSphere();
}

void Chunk::generateSphere() {
    map = new Block**[CHUNK_SIZE];
    for(unsigned int x = 0; x < CHUNK_SIZE; x++) {
        map[x] = new Block*[CHUNK_SIZE];
        for(unsigned int y = 0; y < CHUNK_SIZE; y++) {
            map[x][y] = new Block[CHUNK_SIZE];
            for(unsigned int z = 0; z < CHUNK_SIZE; z++) {
                map[x][y][z] = Block();
                if (sqrt((float) (x-CHUNK_SIZE/2)*(x-CHUNK_SIZE/2) + (y-CHUNK_SIZE/2)*(y-CHUNK_SIZE/2) + (z-CHUNK_SIZE/2)*(z-CHUNK_SIZE/2)) <= CHUNK_SIZE/2) {
                    map[x][y][z].active = true;
                    map[x][y][z].id = 1;
                }
            }
        }
    }
}