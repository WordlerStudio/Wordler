#pragma once

#include <vector>
#include <tuple>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Block {
    float x, y, z;
    float size;
    float r, g, b;
    bool useColor;
    std::string texturePath;
    GLuint textureID;

    Block(
        float x, float y, float z,
        float size = 1.0f,
        float r = 1.0f, float g = 1.0f, float b = 1.0f,
        bool useColor = true,
        const std::string& texturePath = ""
    )
        : x(x), y(y), z(z), size(size),
          r(r), g(g), b(b),
          useColor(useColor),
          texturePath(texturePath),
          textureID(0)
    {}
};

class Game {
    std::vector<Block> blocks;
    SDL_Window* window;
    SDL_GLContext glContext;
    float camX = 0, camY = 0, camZ = -5;
public:
    Game();
    ~Game();
    void placeBlock(float x, float y, float z, float size = 1, const std::string& texturePath = "", bool useColor = true, float r = 1, float g = 0, float b = 0);
    void moveCamera(float dx, float dz);
    void handleInput(bool& running);
    void update();
    bool checkCollision(float nextX, float nextY, float nextZ);
    GLuint loadTextureSDL(const std::string& path);
};