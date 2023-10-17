#include <iostream>
#include "Game.h"
#include "Pawn.h"
#include "Piece.h"

//TODO: will eliminate direct access to _board (especially in non const setting) from outside. Only here for testing purposes

int main() {
    Game* myGame = Game::instance();
    std::cout << myGame->getBoard();
    Pawn* myPawn = new Pawn('w');
    myGame->getBoard().addPiece(myPawn, 3,4);
    std::cout << myGame->getBoard();
    return 0;
}
