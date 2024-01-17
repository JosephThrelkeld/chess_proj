//
// Created by joeyt on 9/25/2023.
//

#include "Game.h"

Game* Game::_instance = nullptr;

Game* Game::instance() {
    if (_instance == nullptr) {
        _instance = new Game;
    }
    return _instance;
}

Game::Game() = default;

Board &Game::getBoard() {
    return this->_board;
}

void Game::setDefaultStart() {
    this->_board.clearAllPieces();
    this->setBackRank(0, 'B');
    this->setFrontRank(1,'B');
    this->setBackRank(7, 'W');
    this->setFrontRank(6,'W');
}

void Game::setBackRank(unsigned int row, char color) {
    this->_board.addPiece(new Rook(color), row, 0);
    this->_board.addPiece(new Knight(color), row, 1);
    this->_board.addPiece(new Bishop(color), row, 2);
    this->_board.addPiece(new Queen(color), row, 3);
    this->_board.addPiece(new King(color), row, 4);
    this->_board.addPiece(new Bishop(color), row, 5);
    this->_board.addPiece(new Knight(color), row, 6);
    this->_board.addPiece(new Rook(color), row, 7);

}
void Game::setFrontRank(unsigned int row, char color) {
    for (int i = 0; i < this->_board.getNumCols(); ++i) {
        this->_board.addPiece(new Pawn(color), row, i);
    }
}

void Game::printBoard() {
    std::cout << this->_board << std::endl;
}

void Game::movePiece(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput) {
    this->_board.movePiece(sRowInput,sColInput,eRowInput,eColInput);
}

std::set<std::tuple<unsigned int, unsigned int>> Game::returnPossMoves(unsigned int rowInput, unsigned int colInput) {
    std::set<std::tuple<unsigned int, unsigned int>> possMoves = {};
    Piece* selectedPiece = this->_board.getPiece(rowInput, colInput);

    //If square doesn't contain piece, there are no possible moves
    if (!selectedPiece) { return possMoves; }

    switch (selectedPiece->getPieceSymbol()) {
        case 'P':
            int direction;
            bool onBeginningRank;
            if (selectedPiece->getColor() == 'W') {
                direction = -1;
                onBeginningRank = rowInput == 6;
            } else {
                direction = 1;
                onBeginningRank = rowInput == 1;
            }
            if (checkMoveBasic(rowInput, colInput, rowInput + direction, colInput)) {
                possMoves.insert({rowInput + direction, colInput});
                if (onBeginningRank && checkMoveBasic(rowInput, colInput, rowInput + (direction * 2), colInput)) {
                    possMoves.insert({rowInput + (direction * 2), colInput});
                }
            }

            if (checkMoveBasic(rowInput, colInput, rowInput + direction, colInput + 1) &&
                this->_board.getPiece(rowInput + direction, colInput + 1)) possMoves.insert({rowInput + direction, colInput + 1});
            if (checkMoveBasic(rowInput, colInput, rowInput + direction, colInput - 1) &&
                this->_board.getPiece(rowInput + direction, colInput - 1)) possMoves.insert({rowInput + direction, colInput - 1});
            break;
        case 'R':
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,-1,0));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,0,-1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,1,0));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,0,1));

            break;
        case 'B':
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,-1,-1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,1,1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,-1,1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,1,-1));

            break;
        case 'N':
            for (auto& currMove : this->knightMoves) {
                int rowDiff;
                int colDiff;
                std::tie(rowDiff,colDiff) = currMove;
                if (checkMoveBasic(rowInput, colInput, rowInput + rowDiff, colInput + colDiff)) possMoves.insert({rowInput + rowDiff, colInput + colDiff});
            }
            break;
        case 'Q':
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,-1,0));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,0,-1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,1,0));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,0,1));

            possMoves.merge(addAllMovesInDirection(rowInput,colInput,-1,-1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,1,1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,-1,1));
            possMoves.merge(addAllMovesInDirection(rowInput,colInput,1,-1));
            break;
        case 'K':
            for (int rowDiff = -1; rowDiff < 2; ++rowDiff) {
                for (int colDiff = -1; colDiff < 2; ++colDiff) {
                    if (checkMoveBasic(rowInput, colInput, rowInput + rowDiff, colInput + colDiff)) possMoves.insert({rowInput + rowDiff, colInput + colDiff});
                }
            }
            break;
        default:
            break;
    }

    return possMoves;
}

//Checking basic move rules:
/*
 * 1. Can't move into square with piece of same color.
 * 2. Can't move off board (duh).
 * */
//Does not check all move rules
bool Game::checkMoveBasic(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput) {
    //We shouldn't have to check for rows and columns being less than 0 as they are all unsigned
    if (sRowInput >= this->_board.getNumRows() ||
        eRowInput >= this->_board.getNumRows() ||
        sColInput >= this->_board.getNumCols() ||
        eColInput >= this->_board.getNumCols()) { return false; }

    Piece* selectedPiece = this->_board.getPiece(sRowInput, sColInput);
    Piece* targetSquarePiece = this->_board.getPiece(eRowInput,eColInput);


    //We can't move if the starting square doesn't contain a piece
    if (!selectedPiece) return false;

    if (targetSquarePiece && selectedPiece->getColor() == targetSquarePiece->getColor()) return false;

    return true;
}

std::set<std::tuple<unsigned int, unsigned int>> Game::addAllMovesInDirection(unsigned int rowInput, unsigned int colInput, int rowDirection, int colDirection) {
    std::set<std::tuple<unsigned int, unsigned int>> directionPossMoves = {};
    int magnitude = 1;
    while (checkMoveBasic(rowInput, colInput, rowInput + (magnitude * rowDirection), colInput + (magnitude * colDirection))) {
        directionPossMoves.insert({rowInput + (magnitude * rowDirection), colInput + (magnitude * colDirection)});
        //If we take a piece we also need to stop
        if (this->_board.getPiece(rowInput + (magnitude * rowDirection), colInput + (magnitude * colDirection))) break;
        ++magnitude;
    }
    return directionPossMoves;
}