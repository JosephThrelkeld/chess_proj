//
// Created by joeyt on 9/25/2023.
//

#ifndef CHESS_PROJ_GAME_H
#define CHESS_PROJ_GAME_H

#include "Board.h"
#include "Pieces/AllPieces.h"
#include <tuple>
#include <set>
#include <stdexcept>

//Using Singleton design pattern as we only want one game running at a time (presumably)
class Game {
public:
    static Game* instance();
    std::set<std::tuple<unsigned int, unsigned int>> returnPossMoves(unsigned int rowInput, unsigned int colInput);
    void printBoard();
    void setDefaultStart();
    std::set<std::tuple<unsigned int, unsigned int>> pieceSqrsAttackingSqr(unsigned int rowInput, unsigned int colInput, char attackingColorSym);
    void movePiece(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput);
    bool checkForChecks(char kingColorToCheck);
protected:
    Game();
private:

    void setBackRank(unsigned int row, char color);
    void setFrontRank(unsigned int row, char color);
    const std::set<std::tuple<int, int>> knightMoves = {{1,2},{1,-2},{-1,2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}};
    bool checkMoveBasic(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput);
    std::set<std::tuple<unsigned int, unsigned int>> addAllMovesInDirection(unsigned int rowInput, unsigned int colInput, int rowDirection, int colDirection);
    static Game* _instance;
    Board _board;
};



#endif //CHESS_PROJ_GAME_H
