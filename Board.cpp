//
// Created by joeyt on 9/25/2023.
//

#include "Board.h"
#include "Pieces/Pawn.h"

Board::Board() : _boardSpaceArr() {}

void Board::addPiece(Piece *inputPiece, unsigned int rowInput, unsigned int colInput) {
    this->_boardSpaceArr[rowInput][colInput] = inputPiece;
}

//Using operator overloading to print board for debugging and it is fun.
std::ostream &operator<<(std::ostream &os, const Board &bd) {
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

unsigned int Board::getNumRows() {
    return NUM_ROWS;
}

unsigned int Board::getNumCols() {
    return NUM_COLS;
}

Piece *Board::getPiece(unsigned int rowInput, unsigned int colInput) {
    if (this->_boardSpaceArr[rowInput][colInput] != nullptr) return this->_boardSpaceArr[rowInput][colInput];
    return nullptr;
}

void Board::movePiece(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput) {
    try {
        if (sRowInput < 0 || sRowInput >= Board::getNumRows() ||
            sColInput < 0 || sColInput >= Board::getNumCols() ||
            eRowInput < 0 || eRowInput >= Board::getNumRows() ||
            eColInput < 0 || eColInput >= Board::getNumCols())
            throw 1;
    }
    catch (...) {
        std::cout << "starting or ending coordinates out of board range";
    }

    this->_boardSpaceArr[eRowInput][eColInput] = this->_boardSpaceArr[sRowInput][sColInput];
    this->_boardSpaceArr[sRowInput][sColInput] = nullptr;
}

void Board::clearPiece(unsigned int rowInput, unsigned int colInput) {
    this->_boardSpaceArr[rowInput][colInput] = nullptr;
}