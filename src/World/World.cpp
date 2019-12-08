#include "World.h"

World::World() {
    generateChunks();
}

void World::generateChunks() {
    map = new Chunk**[CHUNK_SIZE];
    for(unsigned int x = 0; x < CHUNK_SIZE; x++) {
        map[x] = new Chunk*[CHUNK_SIZE];
        for(unsigned int y = 0; y < CHUNK_SIZE; y++) {
            map[x][y] = new Chunk[CHUNK_SIZE];
            for(unsigned int z = 0; z < CHUNK_SIZE; z++) {
                map[x][y][z] = Chunk();
                map[x][y][z].active = true;
            }
        }
    }
}