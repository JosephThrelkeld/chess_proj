#include <iostream>
#include "Game.h"


int main() {
    Game* myGame = Game::instance();

    myGame->runGameLoop();

    return 0;
}