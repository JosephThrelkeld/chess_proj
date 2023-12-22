#include <iostream>
#include "Game.h"
#include "Pieces/Pawn.h"
#include "Pieces/Piece.h"


int main() {
    Game *myGame = Game::instance();
    myGame->printBoard();
    myGame->setDefaultStart();
    myGame->printBoard();
    return 0;
}