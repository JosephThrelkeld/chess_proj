#include <iostream>
#include "Game.h"
#include "Pieces/Pawn.h"
#include "Pieces/Piece.h"


int main() {
    Game *myGame = Game::instance();
    myGame->printBoard();
    myGame->setDefaultStart();
    myGame->printBoard();
    myGame->movePiece(0,3,4,4);
    myGame->printBoard();

    std::cout << myGame->checkForChecks('W') << std::endl;
    myGame->movePiece(6,4,5,3);
    myGame->printBoard();

    std::cout << myGame->checkForChecks('W') << std::endl;
    //std::set<std::tuple<unsigned int, unsigned  int>> piecesAttacking = myGame->pieceSqrsAttackingSqr(2,5, 'B');
    //int rowDirec;
    //int colDirec;
    //for (auto& move : piecesAttacking) {
    //    std::tie(rowDirec, colDirec) = move;
    //    std::cout << rowDirec << " " << colDirec << std::endl;
    //}


    return 0;
}