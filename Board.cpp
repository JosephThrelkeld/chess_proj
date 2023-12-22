//
// Created by joeyt on 9/25/2023.
//

#include "Board.h"
#include "Pieces/Pawn.h"

Board::Board() : _boardSpaceArr() {}

void Board::addPiece(Piece* inputPiece, unsigned int rowInput, unsigned int colInput) {
    this->_boardSpaceArr[rowInput][colInput] = inputPiece;
}
//Using operator overloading to print board for debugging and it is fun.
std::ostream &operator<<(std::ostream &os,const Board& bd) {
    os << "   A   B   C   D   E   F   G   H" << std::endl;
    for (int i = 0; i < Board::NUM_ROWS; ++i) {
        os << 8 - i << " ";
        for (int j = 0; j < Board::NUM_COLS; ++j) {
            os << "|";
            if (bd._boardSpaceArr[i][j] == nullptr) {
                os << "  ";
            } else {
                os << bd._boardSpaceArr[i][j]->getColor() << bd._boardSpaceArr[i][j]->getPieceSymbol();
            }
            os << "|";
        }
        os << std::endl;
    }
    return os;
}

void Board::clearAllPieces() {
    for (int i = 0; i < Board::NUM_ROWS; ++i) {
        for (int j = 0; j < Board::NUM_COLS; ++j) {
            this->_boardSpaceArr[i][j] = nullptr;
        }
    }
}

const unsigned int Board::getNumRows() {
    return NUM_ROWS;
}

const unsigned int Board::getNumCols() {
    return NUM_COLS;
}
