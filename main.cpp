#include <iostream>
#include "Game.h"


int main() {
    //By hand testing right now
    //TODO: Make formalized tests
    Game *myGame = Game::instance();
    myGame->printBoard();
    myGame->setDefaultStart();
    myGame->printBoard();
    myGame->movePiece(0, 3, 4, 4);
    myGame->printBoard();

    std::cout << myGame->checkForChecks('W') << std::endl;
    std::cout << myGame->returnPossMoves(6, 1).size() << std::endl;
    myGame->movePiece(6, 4, 5, 3);
    myGame->printBoard();

    std::cout << myGame->pieceSqrsAttackingSqr(7,4,'B').size() << std::endl;
    std::set<std::tuple<unsigned int, unsigned  int>> possMoves = myGame->returnPossMoves(4,4);
    int rowDirec;
    int colDirec;
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;

    possMoves = myGame->returnPossMoves(7,4);
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;


    myGame->movePiece(7,5,5,5);
    myGame->movePiece(7,6,5,6);
    myGame->printBoard();

    possMoves = myGame->returnPossMoves(7,4);
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;

    myGame->movePiece(4,4,4,7);
    myGame->printBoard();

    possMoves = myGame->returnPossMoves(7,4);
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;


    myGame->movePiece(7,1,5,1);
    myGame->movePiece(7,2,5,2);
    myGame->movePiece(7,3,5,3);
    myGame->printBoard();
    possMoves = myGame->returnPossMoves(7,4);
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;

    myGame->movePiece(7,0,5,0);
    myGame->movePiece(7,7,5,7);
    myGame->printBoard();
    possMoves = myGame->returnPossMoves(7,4);
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;

    myGame->movePiece(5,0,7,0);
    myGame->movePiece(5,7,7,7);
    myGame->printBoard();
    possMoves = myGame->returnPossMoves(7,4);
    for (auto& move : possMoves) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;



    return 0;
}