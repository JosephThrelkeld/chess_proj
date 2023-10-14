//
// Created by joeyt on 9/25/2023.
//

#ifndef CHESS_PROJ_BOARD_H
#define CHESS_PROJ_BOARD_H


#include "Piece.h"
#include <iostream>

//Using operator overloading for testing contents of board because it centralizes all
//the code for the text representation for the board for use in differing informal tests.
class Board {
public:
    Board();
    friend std::ostream& operator<<(std::ostream& os, const Board& bd);
private:
    const static unsigned int NUM_ROWS = 8;
    const static unsigned int NUM_COLS = 8;
    const Piece* boardSpaceArr[NUM_ROWS][NUM_COLS];
};


#endif //CHESS_PROJ_BOARD_H
