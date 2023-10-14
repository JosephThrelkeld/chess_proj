#include <iostream>
#include "Game.h"

int main() {
    Game* myGame = Game::instance();
    std::cout << myGame->gameBoard();
    return 0;
}
