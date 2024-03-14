//
// Created by joeyt on 9/25/2023.
//

#ifndef CHESS_PROJ_GAME_H
#define CHESS_PROJ_GAME_H

#include "Board.h"
#include "Pieces/AllPieces.h"
#include <tuple>
#include <set>
#include <stdexcept>
#include <map>
#include <regex>


//Using Singleton design pattern as we only want one game running at a time (presumably)
class Game {
public:
    static Game *instance();

    std::set<ChessPosition>
    returnPossMoves(ChessPosition position, bool activeMove = true);

    void printBoard();

    void setDefaultStart();

    std::set<ChessPosition>
    pieceSqrsAttackingSqr(ChessPosition position, char attackingColorSym);

    void movePiece(ChessPosition sPosition, ChessPosition ePosition);

    bool checkForChecks(char kingColorToCheck);

    bool checkForCheckMate(char kingColorToCheck);

    void runGameLoop();

protected:
    Game();

private:
    std::vector<std::pair<ChessPosition,ChessPosition>> _moveLog;

    bool canCastle(char color, ChessPosition kingLocation,
                   ChessPosition rookLocation);

    void setBackRank(unsigned int row, char color);

    void setFrontRank(unsigned int row, char color);

    static const inline std::set<ChessMovement> KNIGHT_MOVES{ChessMovement{1,  2},
                                                      ChessMovement{1,  -2},
                                                      ChessMovement{-1, 2},
                                                      ChessMovement{-1, -2},
                                                      ChessMovement{2,  1},
                                                      ChessMovement{2,  -1},
                                                      ChessMovement{-2, 1},
                                                      ChessMovement{-2, -1}};

    bool checkMoveBasic(ChessPosition sPosition, ChessPosition ePosition, bool activeMove);

    std::set<ChessPosition>
    addAllMovesInDirection(ChessPosition position, ChessMovement direcMovement, bool activeMove);

    std::map<ChessPosition, bool> _mapCastlingPiecesHaveMoved;

    static Game *_instance;
    Board _board;

    int turnCounter;

    int convertColChartoInt(char rowCharInput);

    ChessPosition findKing(char colorToFind);


};


#endif //CHESS_PROJ_GAME_H
