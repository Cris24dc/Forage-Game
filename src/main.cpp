#include "game.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game;

    if(!game.init("Forage", false)) {
        return -1;
    }

    while(game.isRunning()) {
        game.handleEvent();
        game.update();
        game.render();
    }

    return 0;
}