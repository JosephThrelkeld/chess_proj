//
// Created by joeyt on 9/25/2023.
//

#include "Game.h"

//TODO: Rewrite functions to only use pair<unsigned int, unsigned int> for coordinate inputs
//TODO: Check to see if actual seperate subclasses for each piece type is necessary (factory?)
Game *Game::_instance = nullptr;

Game *Game::instance() {
    if (_instance == nullptr) {
        _instance = new Game;
    }
    return _instance;
}

Game::Game() { this->setDefaultStart(); };

void Game::setDefaultStart() {
    this->_mapCastlingPiecesHaveMoved = {{{0, 0}, false},
                                         {{0, 4}, false},
                                         {{0, 7}, false},
                                         {{7, 0}, false},
                                         {{7, 4}, false},
                                         {{7, 7}, false}};

    this->_moveLog = {};
    this->_board.clearAllPieces();
    this->setBackRank(0, 'B');
    this->setFrontRank(1, 'B');
    this->setBackRank(7, 'W');
    this->setFrontRank(6, 'W');

    this->turnCounter = 0;
}

void Game::setBackRank(unsigned int row, char color) {
    this->_board.addPiece(new Rook(color), {row, 0});
    this->_board.addPiece(new Knight(color), {row, 1});
    this->_board.addPiece(new Bishop(color), {row, 2});
    this->_board.addPiece(new Queen(color), {row, 3});
    this->_board.addPiece(new King(color), {row, 4});
    this->_board.addPiece(new Bishop(color), {row, 5});
    this->_board.addPiece(new Knight(color), {row, 6});
    this->_board.addPiece(new Rook(color), {row, 7});

}

void Game::setFrontRank(unsigned int row, char color) {
    for (unsigned int i = 0; i < this->_board.getNumCols(); ++i) {
        this->_board.addPiece(new Pawn(color), {row, i});
    }
}

void Game::printBoard() {
    std::cout << this->_board << std::endl;
}


//Using this function to move the piece (_board.movePiece) but also handle all of the considerations
// that the game needs when moving a piece (castling, promotion
void Game::movePiece(ChessPosition sPosition, ChessPosition ePosition) {
    Piece *pieceToMove = this->_board.getPiece(sPosition);
    //When king or rooks move from starting position, we note that down to prevent them from castling later
    if (this->_mapCastlingPiecesHaveMoved.contains(sPosition) &&
        (!this->_mapCastlingPiecesHaveMoved[sPosition])) {
        this->_mapCastlingPiecesHaveMoved[sPosition] = true;
    }
    this->_board.movePiece(sPosition, ePosition);
}

//Using activeMove boolean as argument to prevent recursion due to checkForChecks conditional
std::set<ChessPosition>
Game::returnPossMoves(ChessPosition position, bool activeMove) {
    //TODO: code en passant
    std::set<ChessPosition> possMoves = {};
    Piece *selectedPiece = this->_board.getPiece(position);
    //If square doesn't contain piece, there are no possible moves
    if (!selectedPiece) return possMoves;
    switch (selectedPiece->getPieceSymbol()) {
        case 'P':
            int direction;
            bool onBeginningRank;
            if (selectedPiece->getColor() == 'W') {
                direction = -1;
                onBeginningRank = position.row() == 6;
            } else {
                direction = 1;
                onBeginningRank = position.row() == 1;
            }

            if (checkMoveBasic(position, {position.row() + direction, position.col()}, activeMove) &&
                this->_board.getPiece({position.row() + direction, position.col()}) == nullptr) {
                possMoves.insert({position.row() + direction, position.col()});
                if (onBeginningRank &&
                    checkMoveBasic(position, {position.row() + (direction * 2), position.col()}, activeMove) &&
                    this->_board.getPiece({position.row() + (direction * 2), position.col()}) == nullptr) {
                    possMoves.insert({position.row() + (direction * 2), position.col()});
                }
            }

            if (checkMoveBasic(position, {position.row() + direction, position.col() + 1}, activeMove) &&
                this->_board.getPiece({position.row() + direction, position.col() + 1}))
                possMoves.insert({position.row() + direction, position.col() + 1});
            if (checkMoveBasic(position, {position.row() + direction, position.col() - 1}, activeMove) &&
                this->_board.getPiece({position.row() + direction, position.col() - 1}))
                possMoves.insert({position.row() + direction, position.col() - 1});
            break;
        case 'R':
            possMoves.merge(addAllMovesInDirection(position, {-1,0}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {0,-1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {1,0}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {0,1}, activeMove));

            break;
        case 'B':
            possMoves.merge(addAllMovesInDirection(position, {-1, -1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {1, 1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {-1, 1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {1, -1}, activeMove));

            break;
        case 'N':
            for (auto mvmt : this->KNIGHT_MOVES) {
                if (checkMoveBasic(position, {position.row() + mvmt.rowDel(), position.col() + mvmt.colDel()}, activeMove))
                    possMoves.insert({position.row() + mvmt.rowDel(), position.col() + mvmt.colDel()});
            }
            break;
        case 'Q':
            possMoves.merge(addAllMovesInDirection(position, {-1,0}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {0,-1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {1,0}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {0,1}, activeMove));

            possMoves.merge(addAllMovesInDirection(position, {-1, -1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {1, 1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {-1, 1}, activeMove));
            possMoves.merge(addAllMovesInDirection(position, {1, -1}, activeMove));
            break;
        case 'K':
            //TODO: Make sure King can't take defended pieces
            //Can not move into check, or through check
            for (int rowDiff = -1; rowDiff < 2; ++rowDiff) {
                for (int colDiff = -1; colDiff < 2; ++colDiff) {
                    if (checkMoveBasic(position, {position.row() + rowDiff, position.col() + colDiff}, activeMove)) {
                        possMoves.insert({position.row() + rowDiff, position.col() + colDiff});
                    }

                }
            }

            //Checking Castling as a king move, when moving king, rook will also be moved.
            if (activeMove) {
                if (canCastle(selectedPiece->getColor(), {position.row(), position.col()}, {position.row(), 0}))
                    possMoves.insert({position.row(), 2});
                if (canCastle(selectedPiece->getColor(), {position.row(), position.col()}, {position.row(), 7}))
                    possMoves.insert({position.row(), 6});
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
Game::checkMoveBasic(ChessPosition sPosition, ChessPosition ePosition,
                     bool activeMove) {
    //We shouldn't have to check for rows and columns being less than 0 as they are all unsigned
    if (sPosition.row() >= Board::getNumRows() ||
        ePosition.row() >= Board::getNumRows() ||
        sPosition.col() >= Board::getNumCols() ||
        ePosition.col() >= Board::getNumCols()) { return false; }

    Piece *selectedPiece = this->_board.getPiece(sPosition);
    Piece *targetSquarePiece = this->_board.getPiece(ePosition);

    if (!selectedPiece) return false;
    //Pieces can't capture pieces of the same color, also prevents moving from and to the same square.
    if (targetSquarePiece && selectedPiece->getColor() == targetSquarePiece->getColor()) return false;

    //If King of same color is in check, current move should get the king out of it
    //If move makes King of same color to become in check, that move should not be a possible move
    //|
    //V
    //King of same color shouldn't be in check at the end of the move
    if (activeMove) {
        //Using board movePiece instead of game movepiece to not mess up logic based on whether king or rooks moved
        // before castling
        bool sameColorKingInCheck = false;
        Piece *tempPiece = this->_board.getPiece(ePosition);
        this->_board.movePiece(sPosition, ePosition);
        if (this->checkForChecks(selectedPiece->getColor())) sameColorKingInCheck = true;
        this->_board.movePiece(ePosition, sPosition);
        if (tempPiece) this->_board.addPiece(tempPiece, ePosition);
        if (sameColorKingInCheck) return false;
    }


    return true;
}

std::set<ChessPosition>
Game::addAllMovesInDirection(ChessPosition position, ChessMovement movementDirection,
                             bool activeMove) {
    std::set<ChessPosition> directionPossMoves = {};
    int magnitude = 1;
    ChessPosition currSquare;
    while (checkMoveBasic(position, {position.row() + (magnitude * movementDirection.rowDel()),
                          position.col() + (magnitude * movementDirection.colDel())}, activeMove)) {
        currSquare = {position.row() + (magnitude * movementDirection.rowDel()),
                                   position.col() + (magnitude * movementDirection.colDel())};
        directionPossMoves.insert(currSquare);
        //If we take a piece we also need to stop
        if (this->_board.getPiece(currSquare)) break;
        ++magnitude;
    }
    return directionPossMoves;
}

std::set<ChessPosition>
Game::pieceSqrsAttackingSqr(ChessPosition position, char attackingColorSym) {
    std::set<ChessPosition> sqrsToReturn = {};

    //Putting dummy piece of color opposite of attacking color if empty to only allow pawns to capture on square
    bool emptySq = false;
    if (this->_board.getPiece(position) == nullptr) {
        emptySq = true;
        Pawn *dummyPiece = (attackingColorSym == 'W') ? new Pawn('B') : new Pawn('W');
        this->_board.addPiece(dummyPiece, position);
    }
    for (unsigned int i = 0; i < this->_board.getNumRows(); ++i) {
        for (unsigned int j = 0; j < this->_board.getNumCols(); ++j) {
            if (this->returnPossMoves({i, j}, false).contains(position)) sqrsToReturn.insert({i, j});
        }
    }

    if (emptySq) this->_board.clearPiece(position);
    return sqrsToReturn;
}

bool Game::checkForChecks(char kingColorToCheck) {
    char attackingColorSym = (kingColorToCheck == 'W') ? 'B' : 'W';
    ChessPosition kingLocation = this->findKing(kingColorToCheck);
    return !this->pieceSqrsAttackingSqr(kingLocation,
                                        attackingColorSym).empty();
}

bool Game::checkForCheckMate(char kingColorToCheck) {
    ChessPosition kingLocation = this->findKing(kingColorToCheck);
    if (checkForChecks(kingColorToCheck) &&
        this->returnPossMoves(kingLocation).empty()) {
        for (unsigned int i = 0; i < Board::getNumRows(); ++i) {
            for (unsigned int j = 0; j < Board::getNumCols(); ++j) {
                Piece *currPiece = this->_board.getPiece({i, j});
                //If a piece sharing the attacked king's color has any possible moves, it is not checkmate
                if (currPiece && currPiece->getColor() == kingColorToCheck && !this->returnPossMoves({i,j}).empty()) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

ChessPosition Game::findKing(char colorToFind) {
    ChessPosition kingLocation{};
    for (unsigned int i = 0; i < Board::getNumRows(); ++i) {
        for (unsigned int j = 0; j < Board::getNumCols(); ++j) {
            Piece *currPiece = this->_board.getPiece({i, j});
            if (currPiece && currPiece->getPieceSymbol() == 'K' &&
                currPiece->getColor() == colorToFind)
                kingLocation = {i, j};
        }
    }
    return kingLocation;
}

bool Game::canCastle(char color, ChessPosition kingLocation,
                     ChessPosition rookLocation) {

    if (kingLocation.row() != rookLocation.row() ||
        !this->_mapCastlingPiecesHaveMoved.contains(kingLocation) ||
        !this->_mapCastlingPiecesHaveMoved.contains(rookLocation) ||
        this->_mapCastlingPiecesHaveMoved[kingLocation] ||
        this->_mapCastlingPiecesHaveMoved[rookLocation])
        return false;

    char kingColor;
    char attackingColor;

    if (this->_board.getPiece(kingLocation)->getColor() == 'W') {
        kingColor = 'W';
        attackingColor = 'B';
    } else {
        kingColor = 'B';
        attackingColor = 'W';
    }

    bool validCastle = true;

    int normCastlingDirection = ((int) rookLocation.col() - (int) kingLocation.col()) /
                                abs((int) rookLocation.col() - (int) kingLocation.col());

    //Checking squares between king and rook to be empty
    for (unsigned int i = kingLocation.col();
         i != rookLocation.col(); i += normCastlingDirection) {
        bool x = (this->_board.getPiece({kingLocation.row(), i}) && i != kingLocation.col());
        bool y = !pieceSqrsAttackingSqr({kingLocation.row(), i}, attackingColor).empty();
        bool z = x || y;
        if (z)
            validCastle = false;
    }

    return validCastle;
}

int Game::convertColChartoInt(char rowCharInput) {
    return tolower(rowCharInput) - 'a';
}

void Game::runGameLoop() {
    //TODO: Handle castling move input
    //TODO: Handle pawn promotion
    std::cout << "Starting game" << std::endl;
    bool gameEnded = false;
    bool validMove = false;
    std::regex moveRegex("[a-hA-H][1-8][a-hA-H][1-8]");
    std::string moveStr;
    this->setDefaultStart();
    unsigned int sRowInput;
    unsigned int sColInput;
    unsigned int eRowInput;
    unsigned int eColInput;

    while (!gameEnded) {
        this->printBoard();

        char currColor = (turnCounter % 2 == 0) ? 'W' : 'B';
        if (checkForCheckMate(currColor)) {
            std::cout << "Checkmate!" << std::endl;
            gameEnded = true;
            break;
        }

        while (!validMove) {
            std::cout << "Enter in your move:" << std::endl;
            std::cin >> moveStr;
            if (std::regex_match(moveStr, moveRegex)) {
                sRowInput = 8 - (moveStr[1] - '0');
                sColInput = convertColChartoInt(moveStr[0]);
                eRowInput = 8 - (moveStr[3] - '0');
                eColInput = convertColChartoInt(moveStr[2]);
                if (this->_board.getPiece({sRowInput, sColInput}) &&
                    this->_board.getPiece({sRowInput, sColInput})->getColor() == currColor &&
                    this->returnPossMoves({sRowInput, sColInput}).contains({eRowInput, eColInput})) {
                    validMove = true;
                    this->movePiece({sRowInput, sColInput}, {eRowInput, eColInput});
                } else {
                    std::cout << "Move is invalid." << std::endl;
                }
            } else {
                std::cout << "Move is invalid." << std::endl;
            }
        }


        ++turnCounter;
        validMove = false;
    }
}

