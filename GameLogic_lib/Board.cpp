//
// Created by joeyt on 9/25/2023.
//

#include "Board.h"
#include "../Pieces/Pawn.h"

Board::Board() : _boardSpaceArr() {}

void Board::addPiece(Piece *inputPiece, ChessPosition position) {
    this->_boardSpaceArr[position.row()][position.col()] = inputPiece;
}

//Using operator overloading to print board for debugging and it is fun.
std::ostream &operator<<(std::ostream &os, const Board &bd) {
    os << std::endl;
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

Piece *Board::getPiece(ChessPosition position) {
    return this->_boardSpaceArr[position.row()][position.col()];
}

void Board::movePiece(ChessPosition sPosition, ChessPosition ePosition) {
    try {
        //Since ChessPosition has unsigned ints, don't have to check for them being less than zero.
        if (sPosition.row() >= Board::getNumRows() ||
            sPosition.col() >= Board::getNumCols() ||
            ePosition.row() >= Board::getNumRows() ||
            ePosition.col() >= Board::getNumCols())
            throw 1;
    }
    catch (...) {
        std::cout << "starting or ending coordinates out of board range";
    }

    this->_boardSpaceArr[ePosition.row()][ePosition.col()] = this->_boardSpaceArr[sPosition.row()][sPosition.col()];
    this->_boardSpaceArr[sPosition.row()][sPosition.col()] = nullptr;
}

void Board::clearPiece(ChessPosition position) {
    this->_boardSpaceArr[position.row()][position.col()] = nullptr;
}