#include <classes/game.hpp>
#include <internal/glu.h>

float yaw = 0.0f; 
float pitch = 0.0f;
float camSpeed = 0.1f;
float mouseSensitivity = 0.1f;

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    window = SDL_CreateWindow("Wordler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
}

Game::~Game() {
    IMG_Quit();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::placeBlock(float x, float y, float z, float size, const std::string& texturePath, bool useColor, float r, float g , float b) {
    Block block(x, y, z, size, r, g, b, useColor, texturePath);
    if (!texturePath.empty()) {
        block.textureID = loadTextureSDL(texturePath);
    }
    blocks.push_back(block);
}

void Game::moveCamera(float dx, float dz) {
    camX += dx;
    camZ += dz;
}

bool Game::checkCollision(float nextX, float nextY, float nextZ) {
    float playerSize = 0.4f;
    for (auto& b : blocks) {
        float s = b.size / 2.0f;
        bool overlapX = fabs(nextX - b.x) < (playerSize + s);
        bool overlapY = fabs(nextY - b.y) < (playerSize + s);
        bool overlapZ = fabs(nextZ - b.z) < (playerSize + s);
        if (overlapX && overlapY && overlapZ) return true;
    }
    return false;
}

void Game::handleInput(bool& running) {
    SDL_Event e;
    int dx, dy;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = false;

        if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_w: {
                    float nextX = camX + sin(yaw) * camSpeed;
                    float nextZ = camZ + cos(yaw) * camSpeed;
                    if (!checkCollision(nextX, camY, nextZ)) {
                        camX = nextX;
                        camZ = nextZ;
                    }
                    break;
                }
                case SDLK_s: {
                    float nextX = camX - sin(yaw) * camSpeed;
                    float nextZ = camZ - cos(yaw) * camSpeed;
                    if (!checkCollision(nextX, camY, nextZ)) {
                        camX = nextX;
                        camZ = nextZ;
                    }
                    break;
                }
                case SDLK_a: {
                    float nextX = camX - cos(yaw) * camSpeed;
                    float nextZ = camZ + sin(yaw) * camSpeed;
                    if (!checkCollision(nextX, camY, nextZ)) {
                        camX = nextX;
                        camZ = nextZ;
                    }
                    break;
                }
                case SDLK_d: {
                    float nextX = camX + cos(yaw) * camSpeed;
                    float nextZ = camZ - sin(yaw) * camSpeed;
                    if (!checkCollision(nextX, camY, nextZ)) {
                        camX = nextX;
                        camZ = nextZ;
                    }
                    break;
                }
            }
        }

        if (e.type == SDL_MOUSEMOTION) {
            dx = e.motion.xrel;
            dy = e.motion.yrel;
            yaw   -= dx * mouseSensitivity * 0.01f;
            pitch -= dy * mouseSensitivity * 0.01f;

            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }
    }
}

GLuint Game::loadTextureSDL(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        printf("Failed to load texture %s: %s\n", path.c_str(), IMG_GetError());
        return 0;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    GLint format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        surface->w,
        surface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        surface->pixels
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    SDL_FreeSurface(surface);
    return tex;
}

void Game::update() {
    glClearColor(0.1f,0.1f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0, 800.0/600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float lx = cos(pitch) * sin(yaw);
    float ly = sin(pitch);
    float lz = cos(pitch) * cos(yaw);

    lookAt(
        camX, camY, camZ,
        camX + lx, camY + ly, camZ + lz, 
        0.0f, 1.0f, 0.0f
    );

    for(auto& b : blocks) {
        glBegin(GL_QUADS);
        glColor3f(b.r,b.g,b.b);
        float s = b.size/2;
        float x = b.x, y = b.y, z = b.z;
        // front
        glVertex3f(x-s, y-s, z+s);
        glVertex3f(x+s, y-s, z+s);
        glVertex3f(x+s, y+s, z+s);
        glVertex3f(x-s, y+s, z+s);
        // back
        glVertex3f(x-s, y-s, z-s);
        glVertex3f(x+s, y-s, z-s);
        glVertex3f(x+s, y+s, z-s);
        glVertex3f(x-s, y+s, z-s);
        // top
        glVertex3f(x-s, y+s, z-s);
        glVertex3f(x+s, y+s, z-s);
        glVertex3f(x+s, y+s, z+s);
        glVertex3f(x-s, y+s, z+s);
        // bottom
        glVertex3f(x-s, y-s, z-s);
        glVertex3f(x+s, y-s, z-s);
        glVertex3f(x+s, y-s, z+s);
        glVertex3f(x-s, y-s, z+s);
        // left
        glVertex3f(x-s, y-s, z-s);
        glVertex3f(x-s, y+s, z-s);
        glVertex3f(x-s, y+s, z+s);
        glVertex3f(x-s, y-s, z+s);
        // right
        glVertex3f(x+s, y-s, z-s);
        glVertex3f(x+s, y+s, z-s);
        glVertex3f(x+s, y+s, z+s);
        glVertex3f(x+s, y-s, z+s);
        glEnd();
    }

    SDL_GL_SwapWindow(window);
    SDL_SetRelativeMouseMode(SDL_TRUE);
}