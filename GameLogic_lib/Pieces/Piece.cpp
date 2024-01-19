//
// Created by joseph on 10/14/23.
//

#include "Piece.h"

Piece::Piece(char colorInput, char pieceSymbolInput, std::string pieceNameInput)
: color(colorInput), pieceSymbol(pieceSymbolInput), pieceName(pieceNameInput) {}

const char Piece::getColor() const {
    return color;
}

const char Piece::getPieceSymbol() const {
    return pieceSymbol;
}

const std::string &Piece::getPieceName() const {
    return pieceName;
}
