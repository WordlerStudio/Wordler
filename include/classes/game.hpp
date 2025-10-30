#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>
#include <optional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <classes/camera.hpp>
#include <classes/vec.hpp>
#include <classes/color.hpp>

struct Block {
    Vec3f pos;
    float size;

    // TODO: transparency support with ColorRGBA
    std::optional<ColorRGB> color;

    std::string texturePath;
    GLuint textureID;

    Block(Vec3f pos, float size, const std::string& texturePath, std::optional<ColorRGB> color = std::nullopt)
        : pos(pos), size(size),
          color(color),
          texturePath(texturePath),
          textureID(0)
    {}
};

class Game {
    std::vector<Block> blocks;
    SDL_Window* window;
    SDL_GLContext glContext;
    Camera cam = Camera(Vec3f { 0, -5, 0 });
public:
    Game();
    ~Game();
    void placeBlock(Vec3f pos, float size, const std::string& texturePath = "", std::optional<ColorRGB> color = std::nullopt);
    void moveCamera(Vec3f off);
    void handleInput(bool& running);
    void update(bool& running);
    bool checkCollision(Vec3f next);
    GLuint loadTextureSDL(const std::string& path);
};
