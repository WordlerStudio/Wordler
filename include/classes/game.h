#pragma once

#include <vector>
#include <tuple>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <cmath>

struct Block {
    float x, y, z;
    float size;
    float r, g, b;
    Block(float x, float y, float z, float size = 1.0f, float r = 1, float g = 0, float b = 0)
        : x(x), y(y), z(z), size(size), r(r), g(g), b(b) {}
};

class Game {
    std::vector<Block> blocks;
    SDL_Window* window;
    SDL_GLContext glContext;
    float camX = 0, camY = 0, camZ = -5;
public:
    Game();
    ~Game();
    void placeBlock(float x, float y, float z, float size = 1.0f);
    void moveCamera(float dx, float dz);
    void handleInput(bool& running);
    void update();
};