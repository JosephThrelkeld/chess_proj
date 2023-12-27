//
// Created by joeyt on 9/25/2023.
//

#ifndef CHESS_PROJ_BOARD_H
#define CHESS_PROJ_BOARD_H

#include "Pieces/Piece.h"
#include <iostream>

//Using operator overloading for testing contents of board because it centralizes all
//the code for the text representation for the board for use in differing informal tests.

/*
 * Using array of pointers to Piece classes to conveniently check for empty squares or not.
 * (array element == nullptr or has a piece there).
 * Alternatives include just have an extra square class or having an "Empty" Piece, but seems unnecessary.
 */
class Board {
public:
    Board();
    friend std::ostream& operator<<(std::ostream& os, const Board& bd);
    void addPiece(Piece* inputPiece, unsigned int rowInput, unsigned int colInput);
    void movePiece(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput);
    Piece* getPiece(unsigned int rowInput, unsigned int colInput);
    void clearAllPieces();
    static unsigned int getNumRows();
    static unsigned int getNumCols();
private:
    const static unsigned int NUM_ROWS = 8;
    const static unsigned int NUM_COLS = 8;
    Piece* _boardSpaceArr[NUM_ROWS][NUM_COLS];
};


#endif //CHESS_PROJ_BOARD_H
