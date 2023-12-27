//
// Created by joeyt on 9/25/2023.
//

#ifndef CHESS_PROJ_GAME_H
#define CHESS_PROJ_GAME_H

#include "Board.h"
#include "Pieces/AllPieces.h"

//Using Singleton design pattern as we only want one game running at a time (presumably)
class Game {
public:
    static Game* instance();
    void printBoard();
    void setDefaultStart();
    void movePiece(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput);
    void setBackRank(unsigned int row, char color);
    void setFrontRank(unsigned int row, char color);
protected:
    Game();
private:
    Board &getBoard();
    static Game* _instance;
    Board _board;
};



#endif //CHESS_PROJ_GAME_H
