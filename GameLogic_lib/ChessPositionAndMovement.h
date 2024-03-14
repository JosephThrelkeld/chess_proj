//
// Created by joeyt on 3/13/2024.
//

#ifndef CHESSPROJECT_SQUAREPOSITION_H
#define CHESSPROJECT_SQUAREPOSITION_H

#endif //CHESSPROJECT_SQUAREPOSITION_H

#include <tuple>
#include<set>
struct ChessPosition {
public:
    ChessPosition() : _row(9) , _column(9) {};
    ChessPosition(unsigned int row, unsigned col) : _row(row), _column(col) {};
    [[nodiscard]] unsigned int row() const {
        return _row;
    }
    [[nodiscard]] unsigned int col() const {
        return _column;
    }
private:
    unsigned int _row;
    unsigned  int _column;
};

inline bool operator<(const ChessPosition& lhs, const ChessPosition& rhs) {
    return std::pair{rhs.row(), rhs.col()} < std::pair{lhs.row(), lhs.col()};
}
inline bool operator==(const ChessPosition& lhs, const ChessPosition& rhs) {
    return lhs.row() == rhs.row() && rhs.col() == lhs.col();
}

struct ChessMovement {
    ChessMovement(int rowD, int colD) : _rowDisplacement(rowD), _columnDisplacement(colD) {};
    [[nodiscard]] int rowDel() const {
        return _rowDisplacement;
    }
    [[nodiscard]] int colDel() const {
        return _columnDisplacement;
    }
private:
    int _rowDisplacement;
    int _columnDisplacement;
};

//Defining special operator so ChessMovement can be in sets
inline bool operator<(const ChessMovement& lhs, const ChessMovement& rhs) {
    return std::pair{rhs.rowDel(), rhs.colDel()} < std::pair{lhs.rowDel(), lhs.colDel()};
}