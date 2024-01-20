//
// Created by joeyt on 9/25/2023.
//

#include "Game.h"

Game *Game::_instance = nullptr;

Game *Game::instance() {
    if (_instance == nullptr) {
        _instance = new Game;
    }
    return _instance;
}

Game::Game() = default;

void Game::setDefaultStart() {
    this->_mapCastlingPiecesHaveMoved = {{{0, 0}, false},
                                         {{0, 4}, false},
                                         {{0, 7}, false},
                                         {{7, 0}, false},
                                         {{7, 4}, false},
                                         {{7, 7}, false}};

    this->_board.clearAllPieces();
    this->setBackRank(0, 'B');
    this->setFrontRank(1, 'B');
    this->setBackRank(7, 'W');
    this->setFrontRank(6, 'W');
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
    Piece *pieceToMove = this->_board.getPiece(sRowInput, sColInput);
    //When king or rooks move from starting position, we note that down to prevent them from castling later
    if (this->_mapCastlingPiecesHaveMoved.contains({sRowInput, sColInput}) &&
        (!this->_mapCastlingPiecesHaveMoved[{sRowInput, sColInput}])) {
        this->_mapCastlingPiecesHaveMoved[{sRowInput, sColInput}] = true;
    }
    this->_board.movePiece(sRowInput, sColInput, eRowInput, eColInput);
}

//Using activeMove boolean as argument to prevent recursion due to checkForChecks conditional
std::set<std::tuple<unsigned int, unsigned int>>
Game::returnPossMoves(unsigned int rowInput, unsigned int colInput, bool activeMove) {
    std::set<std::tuple<unsigned int, unsigned int>> possMoves = {};
    Piece *selectedPiece = this->_board.getPiece(rowInput, colInput);

    //If square doesn't contain piece, there are no possible moves
    if (!selectedPiece ||
        (activeMove &&
         selectedPiece->getPieceSymbol() != 'K' &&
         checkForChecks(selectedPiece->getColor())))
        return possMoves;

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

            if (checkMoveBasic(rowInput, colInput, rowInput + direction, colInput) &&
                this->_board.getPiece(rowInput + direction, colInput) == nullptr) {
                possMoves.insert({rowInput + direction, colInput});
                if (onBeginningRank && checkMoveBasic(rowInput, colInput, rowInput + (direction * 2), colInput) &&
                    this->_board.getPiece(rowInput + (direction * 2), colInput) == nullptr) {
                    possMoves.insert({rowInput + (direction * 2), colInput});
                }
            }

            if (checkMoveBasic(rowInput, colInput, rowInput + direction, colInput + 1) &&
                this->_board.getPiece(rowInput + direction, colInput + 1))
                possMoves.insert({rowInput + direction, colInput + 1});
            if (checkMoveBasic(rowInput, colInput, rowInput + direction, colInput - 1) &&
                this->_board.getPiece(rowInput + direction, colInput - 1))
                possMoves.insert({rowInput + direction, colInput - 1});
            break;
        case 'R':
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, -1, 0));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 0, -1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 1, 0));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 0, 1));

            break;
        case 'B':
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, -1, -1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 1, 1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, -1, 1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 1, -1));

            break;
        case 'N':
            for (auto &currMove : this->KNIGHT_MOVES) {
                int rowDiff;
                int colDiff;
                std::tie(rowDiff, colDiff) = currMove;
                if (checkMoveBasic(rowInput, colInput, rowInput + rowDiff, colInput + colDiff))
                    possMoves.insert({rowInput + rowDiff, colInput + colDiff});
            }
            break;
        case 'Q':
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, -1, 0));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 0, -1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 1, 0));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 0, 1));

            possMoves.merge(addAllMovesInDirection(rowInput, colInput, -1, -1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 1, 1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, -1, 1));
            possMoves.merge(addAllMovesInDirection(rowInput, colInput, 1, -1));
            break;
        case 'K':
            //Can not move into check, or through check
            for (int rowDiff = -1; rowDiff < 2; ++rowDiff) {
                for (int colDiff = -1; colDiff < 2; ++colDiff) {
                    if (checkMoveBasic(rowInput, colInput, rowInput + rowDiff, colInput + colDiff) &&
                            (!activeMove || pieceSqrsAttackingSqr(rowInput + rowDiff, colInput + colDiff,
                                                              (selectedPiece->getColor() == 'W') ? 'B' : 'W').empty())) {
                        possMoves.insert({rowInput + rowDiff, colInput + colDiff});
                    }

                }
            }

            //Checking Castling as a king move, when moving king, rook will also be moved.
            if (activeMove) {
                if (canCastle(selectedPiece->getColor(), {rowInput, colInput}, {rowInput, 0}))
                    possMoves.insert({rowInput, 2});
                if (canCastle(selectedPiece->getColor(), {rowInput, colInput}, {rowInput, 7}))
                    possMoves.insert({rowInput, 6});
            }

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
bool
Game::checkMoveBasic(unsigned int sRowInput, unsigned int sColInput, unsigned int eRowInput, unsigned int eColInput) {
    //We shouldn't have to check for rows and columns being less than 0 as they are all unsigned
    if (sRowInput >= Board::getNumRows() ||
        eRowInput >= Board::getNumRows() ||
        sColInput >= Board::getNumCols() ||
        eColInput >= Board::getNumCols()) { return false; }

    Piece *selectedPiece = this->_board.getPiece(sRowInput, sColInput);
    Piece *targetSquarePiece = this->_board.getPiece(eRowInput, eColInput);


    //We can't move if the starting square doesn't contain a piece
    if (!selectedPiece) return false;

    //Pieces can't capture pieces of the same color, also prevents moving from and to the same square.
    if (targetSquarePiece && selectedPiece->getColor() == targetSquarePiece->getColor()) return false;

    return true;
}

std::set<std::tuple<unsigned int, unsigned int>>
Game::addAllMovesInDirection(unsigned int rowInput, unsigned int colInput, int rowDirection, int colDirection) {
    std::set<std::tuple<unsigned int, unsigned int>> directionPossMoves = {};
    int magnitude = 1;
    while (checkMoveBasic(rowInput, colInput, rowInput + (magnitude * rowDirection),
                          colInput + (magnitude * colDirection))) {
        directionPossMoves.insert({rowInput + (magnitude * rowDirection), colInput + (magnitude * colDirection)});
        //If we take a piece we also need to stop
        if (this->_board.getPiece(rowInput + (magnitude * rowDirection), colInput + (magnitude * colDirection))) break;
        ++magnitude;
    }
    return directionPossMoves;
}

std::set<std::tuple<unsigned int, unsigned int>>
Game::pieceSqrsAttackingSqr(unsigned int rowInput, unsigned int colInput, char attackingColorSym) {
    std::set<std::tuple<unsigned int, unsigned int>> sqrsToReturn = {};

    //Putting dummy piece of color opposite of attacking color if empty to only allow pawns to capture on square
    bool emptySq = false;
    if (this->_board.getPiece(rowInput, colInput) == nullptr) {
        emptySq = true;
        Pawn *dummyPiece = (attackingColorSym == 'W') ? new Pawn('B') : new Pawn('W');
        this->_board.addPiece(dummyPiece, rowInput, colInput);
    }
    for (int i = 0; i < this->_board.getNumRows(); ++i) {
        for (int j = 0; j < this->_board.getNumCols(); ++j) {
            if (this->returnPossMoves(i, j, false).contains({rowInput, colInput})) sqrsToReturn.insert({i, j});
        }
    }

    if (emptySq) this->_board.clearPiece(rowInput, colInput);
    return sqrsToReturn;
}

bool Game::checkForChecks(char kingColorToCheck) {
    char attackingColorSym = (kingColorToCheck == 'W') ? 'B' : 'W';

    std::tuple<unsigned int, unsigned int> kingLocation;
    for (int i = 0; i < Board::getNumRows(); ++i) {
        for (int j = 0; j < Board::getNumCols(); ++j) {
            Piece *currPiece = this->_board.getPiece(i, j);
            if (currPiece && currPiece->getPieceSymbol() == 'K' &&
                currPiece->getColor() == kingColorToCheck)
                kingLocation = {i, j};
        }
    }

    return !this->pieceSqrsAttackingSqr(std::get<0>(kingLocation), std::get<1>(kingLocation),
                                        attackingColorSym).empty();
}

bool Game::canCastle(char color, std::tuple<unsigned int, unsigned int> kingLocation,
                     std::tuple<unsigned int, unsigned int> rookLocation) {

    if (std::get<0>(kingLocation) != std::get<0>(rookLocation) ||
        !this->_mapCastlingPiecesHaveMoved.contains(kingLocation) ||
        !this->_mapCastlingPiecesHaveMoved.contains(rookLocation) ||
        this->_mapCastlingPiecesHaveMoved[kingLocation] ||
        this->_mapCastlingPiecesHaveMoved[rookLocation])
        return false;

    char kingColor;
    char attackingColor;

    if (this->_board.getPiece(std::get<0>(kingLocation), std::get<1>(kingLocation))->getColor() == 'W') {
        kingColor = 'W';
        attackingColor = 'B';
    } else {
        kingColor = 'B';
        attackingColor = 'W';
    }

    bool validCastle = true;

    int normCastlingDirection = ((int) std::get<1>(rookLocation) - (int) std::get<1>(kingLocation)) /
                                abs((int) std::get<1>(rookLocation) - (int) std::get<1>(kingLocation));

    //Checking squares between king and rook to be empty
    for (int i = std::get<1>(kingLocation);
         i != std::get<1>(rookLocation); i += normCastlingDirection) {
        bool x = (this->_board.getPiece(std::get<0>(kingLocation), i) && i != std::get<1>(kingLocation));
        bool y = !pieceSqrsAttackingSqr(std::get<0>(kingLocation), i, attackingColor).empty();
        bool z = x || y;
        if (z)
            validCastle = false;
    }

    return validCastle;
}