#include <classes/game.h>

int main() {
    Game game;
    bool running = true;

    game.placeBlock(0,0,0);

    while(running) {
        game.handleInput(running);
        game.update();
    }

    return 0;
}