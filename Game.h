//
// Created by joeyt on 9/25/2023.
//

#ifndef CHESS_PROJ_GAME_H
#define CHESS_PROJ_GAME_H

#include "Board.h"

//Using Singleton design pattern as we only want one game running at a time (presumably)
class Game {
public:
    static Game* instance();
    Board &getBoard();
protected:
    Game();
private:
    static Game* _instance;
    Board _board;
};



#endif //CHESS_PROJ_GAME_H
