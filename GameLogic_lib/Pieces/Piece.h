//
// Created by joseph on 10/14/23.
//

#ifndef CHESS_PROJ_PIECE_H
#define CHESS_PROJ_PIECE_H

//Using character for color for simplicity and far-off option for multiple players (as opposed to bool isWhite)
//Using b for black and w for white
/*
 * Using char and string for piece ID, rather than just checking for what subclass the piece is.
 * Both char and string may not be needed but char would be simple for checking piece identity and
 * full piece name may be useful for debugging and ensuring no overlaps.
 */
#include <tuple>
#include <string>


class Piece {
public:
    Piece(char colorInput, char pieceSymbolInput, std::string pieceNameInput);
protected:
    const char color;
public:
    const char getColor() const;
    const char getPieceSymbol() const;
    const std::string &getPieceName() const;
protected:
    const char pieceSymbol;
    const std::string pieceName;
};


#endif //CHESS_PROJ_PIECE_H
