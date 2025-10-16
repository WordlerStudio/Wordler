#include <classes/game.hpp>
#include <internal/glu.h>

float yaw = 0.0f; 
float pitch = 0.0f;
float camSpeed = 0.1f;
float mouseSensitivity = 0.1f;

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Wordler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
}

Game::~Game() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::placeBlock(float x, float y, float z, float size) {
    blocks.emplace_back(x, y, z, size);
}

void Game::moveCamera(float dx, float dz) {
    camX += dx;
    camZ += dz;
}

void Game::handleInput(bool& running) {
    SDL_Event e;
    int dx, dy;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = false;

        if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_w: camX += sin(yaw) * camSpeed; camZ += cos(yaw) * camSpeed; break;
                case SDLK_s: camX -= sin(yaw) * camSpeed; camZ -= cos(yaw) * camSpeed; break;
                case SDLK_a: camX -= cos(yaw) * camSpeed; camZ += sin(yaw) * camSpeed; break;
                case SDLK_d: camX += cos(yaw) * camSpeed; camZ -= sin(yaw) * camSpeed; break;
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