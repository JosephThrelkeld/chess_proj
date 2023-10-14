//
// Created by joeyt on 9/25/2023.
//

#include "Board.h"

Board::Board() : boardSpaceArr() {

}

std::ostream &operator<<(std::ostream &os,const Board& bd) {
    for (int i = 0; i < Board::NUM_ROWS; ++i) {
        for (int j = 0; j < Board::NUM_COLS; ++j) {
            os << "|";
            if (bd.boardSpaceArr[i][j] == nullptr) {
                os << " ";
            }
            os << "|";
        }
        os << std::endl;
    }
    return os;
}
