//
// Created by joeyt on 9/25/2023.
//

#include "Board.h"
#include "Pawn.h"

Board::Board() : _boardSpaceArr() {
    _boardSpaceArr[1][2] = new Pawn('w');
}

void Board::addPiece(Piece* inputPiece, unsigned int rowInput, unsigned int colInput) {
    this->_boardSpaceArr[rowInput][colInput] = inputPiece;
}

std::ostream &operator<<(std::ostream &os,const Board& bd) {
    for (int i = 0; i < Board::NUM_ROWS; ++i) {
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
