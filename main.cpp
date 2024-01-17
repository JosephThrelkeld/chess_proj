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

    std::set<std::tuple<unsigned int, unsigned  int>> possMoves = myGame->returnPossMoves(4,4);
    int rowDirec;
    int colDirec;
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    return 0;
}