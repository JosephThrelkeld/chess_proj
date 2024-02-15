#include "doctest.h"
#include "Game.h"

//Utility function for debugging tests involving potential move sets
void printMoveSet(std::set<std::tuple<unsigned int, unsigned int>> moveSet) {
    int rowDirec;
    int colDirec;
    for (auto &move: moveSet) {
        std::tie(rowDirec, colDirec) = move;
        std::cout << rowDirec << " " << colDirec << std::endl;
    }
    std::cout << std::endl;
}

Game *testGame = Game::instance();

TEST_CASE("Basic Game Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    CHECK(testGame->returnPossMoves(1, 1) == std::set<std::tuple<unsigned int, unsigned int>>{{2, 1},
                                                                                              {3, 1}});

    testGame->movePiece(1, 1, 2, 1);

    CHECK(testGame->returnPossMoves(2, 1) == std::set<std::tuple<unsigned int, unsigned int>>{{3, 1}});

    testGame->movePiece(7, 3, 5, 4);
    testGame->movePiece(0, 3, 2, 3);
    testGame->movePiece(1, 4, 2, 5);

    printMoveSet(testGame->returnPossMoves(2, 1));
    //If King is in check, other pieces of same color should have no possible moves
    CHECK(testGame->returnPossMoves(2, 1).empty());

    //The king should still be able to move (with normal king move restrictions)
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3}});

    //Checking moves of empty square should return empty set
    CHECK(testGame->returnPossMoves(1, 1).empty());
}

TEST_CASE("Pawn Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    CHECK(testGame->returnPossMoves(6, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{5, 4},
                                                                                              {4, 4}});

    testGame->movePiece(6, 4, 4, 4);

    CHECK(testGame->returnPossMoves(4, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{3, 4}});

    testGame->movePiece(1, 4, 3, 4);

    CHECK(testGame->returnPossMoves(4, 4).empty());

    testGame->movePiece(1, 5, 3, 5);

    CHECK(testGame->returnPossMoves(4, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{3, 5}});
}

TEST_CASE("Knight Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    CHECK(testGame->returnPossMoves(7, 1) == std::set<std::tuple<unsigned int, unsigned int>>{{5, 0},
                                                                                              {5, 2}});

    //Testing all move directions in center of
    testGame->movePiece(7, 1, 4, 2);
    testGame->movePiece(6, 1, 5, 7);
    testGame->movePiece(6, 3, 4, 7);


    CHECK(testGame->returnPossMoves(4, 2) == std::set<std::tuple<unsigned int, unsigned int>>{{6, 1},
                                                                                              {6, 3},
                                                                                              {5, 0},
                                                                                              {3, 0},
                                                                                              {2, 1},
                                                                                              {2, 3},
                                                                                              {3, 4},
                                                                                              {5, 4}});

    //Testing to see if knight can jump over enemy pieces
    testGame->movePiece(1, 2, 3, 2);

    CHECK(testGame->returnPossMoves(4, 2) == std::set<std::tuple<unsigned int, unsigned int>>{{6, 1},
                                                                                              {6, 3},
                                                                                              {5, 0},
                                                                                              {3, 0},
                                                                                              {2, 1},
                                                                                              {2, 3},
                                                                                              {3, 4},
                                                                                              {5, 4}});
}

TEST_CASE("Bishop Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    CHECK(testGame->returnPossMoves(7, 2).size() == 0);

    testGame->movePiece(6, 3, 4, 3);


    CHECK(testGame->returnPossMoves(7, 2) == std::set<std::tuple<unsigned int, unsigned int>>{{6, 3},
                                                                                              {5, 4},
                                                                                              {4, 5},
                                                                                              {3, 6},
                                                                                              {2, 7}});

    testGame->movePiece(7, 2, 4, 5);

    CHECK(testGame->returnPossMoves(4, 5) == std::set<std::tuple<unsigned int, unsigned int>>{{5, 6},
                                                                                              {3, 4},
                                                                                              {2, 3},
                                                                                              {1, 2},
                                                                                              {7, 2},
                                                                                              {6, 3},
                                                                                              {5, 4},
                                                                                              {3, 6},
                                                                                              {2, 7}});
}

TEST_CASE("Rook Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    CHECK(testGame->returnPossMoves(0, 0).size() == 0);

    testGame->movePiece(0, 0, 3, 3);

    CHECK(testGame->returnPossMoves(3, 3) == std::set<std::tuple<unsigned int, unsigned int>>{{2, 3},
                                                                                              {4, 3},
                                                                                              {5, 3},
                                                                                              {6, 3},
                                                                                              {3, 0},
                                                                                              {3, 1},
                                                                                              {3, 2},
                                                                                              {3, 4},
                                                                                              {3, 5},
                                                                                              {3, 6},
                                                                                              {3, 7}});
}

TEST_CASE("Queen Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    CHECK(testGame->returnPossMoves(0, 3).size() == 0);


    testGame->movePiece(0, 3, 3, 3);

    CHECK(testGame->returnPossMoves(3, 3) == std::set<std::tuple<unsigned int, unsigned int>>{{2, 2},
                                                                                              {2, 3},
                                                                                              {2, 4},
                                                                                              {3, 0},
                                                                                              {3, 1},
                                                                                              {3, 2},
                                                                                              {3, 4},
                                                                                              {3, 5},
                                                                                              {3, 6},
                                                                                              {3, 7},
                                                                                              {4, 2},
                                                                                              {4, 3},
                                                                                              {4, 4},
                                                                                              {5, 1},
                                                                                              {5, 3},
                                                                                              {5, 5},
                                                                                              {6, 0},
                                                                                              {6, 3},
                                                                                              {6, 6}});
}

TEST_CASE("King Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    CHECK(testGame->returnPossMoves(0, 4).empty());

    testGame->movePiece(0, 4, 3, 3);
    //Check all basic king moves
    CHECK(testGame->returnPossMoves(3, 3) == std::set<std::tuple<unsigned int, unsigned int>>{{2, 2},
                                                                                              {2, 3},
                                                                                              {2, 4},
                                                                                              {3, 2},
                                                                                              {3, 4},
                                                                                              {4, 2},
                                                                                              {4, 3},
                                                                                              {4, 4}});

    testGame->movePiece(3, 3, 4, 4);

    //King shouldn't be able to move into check
    CHECK(testGame->returnPossMoves(4, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{3, 3},
                                                                                              {3, 4},
                                                                                              {3, 5},
                                                                                              {4, 3},
                                                                                              {4, 5}});


    testGame->setDefaultStart();

    testGame->movePiece(0, 1, 3, 1);
    testGame->movePiece(0, 2, 3, 2);
    testGame->movePiece(0, 3, 3, 3);

    //Checking for castling one direction
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3},
                                                                                              {0, 2}});

    testGame->movePiece(7, 2, 0, 2);

    //King shouldn't be able to move if enemy piece is blocking
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3}});

    testGame->movePiece(0, 2, 7, 2);
    testGame->movePiece(0, 5, 4, 7);
    testGame->movePiece(0, 6, 3, 6);

    //Checking to see for castling both ways
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3},
                                                                                              {0, 2},
                                                                                              {0, 5},
                                                                                              {0, 6}});


    testGame->movePiece(7, 0, 4, 4);
    testGame->movePiece(1, 4, 2, 7);

    //King shouldn't be able to castle out of check
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3},
                                                                                              {0, 5}});
    //Testing checkForChecks function
    CHECK(testGame->checkForChecks('B'));

    testGame->movePiece(4, 4, 4, 5);
    testGame->movePiece(3, 1, 1, 4);
    testGame->movePiece(1, 5, 3, 7);

    printMoveSet(testGame->returnPossMoves(0, 4));
    //King shouldn't be able to castle through check
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3},
                                                                                              {0, 2}});

    testGame->movePiece(0, 0, 3, 0);

    //Can't castle if rook is not there
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3}});

    testGame->movePiece(3, 0, 0, 0);

    //Can't castle if rook moves, even if it moves back
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3}});

    testGame->movePiece(4, 5, 4, 0);

    //Rechecking for next test
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3},
                                                                                              {0, 5},
                                                                                              {0, 6},
                                                                                              {1, 5}});

    testGame->movePiece(0, 4, 3, 4);
    testGame->movePiece(3, 4, 0, 4);

    //Can't castle if king moves and then moves back
    CHECK(testGame->returnPossMoves(0, 4) == std::set<std::tuple<unsigned int, unsigned int>>{{0, 3},
                                                                                              {0, 5},
                                                                                              {1, 5}});
}

TEST_CASE("Check and Checkmate Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    testGame->movePiece(7, 3, 5, 4);
    testGame->movePiece(1, 4, 2, 7);

    CHECK(testGame->checkForChecks('B'));

    CHECK(!testGame->checkForCheckMate('B'));

    testGame->movePiece(0, 2, 2, 4);

    //Pieces shouldn't be able to move and put their king in check
    CHECK(testGame->returnPossMoves(2, 4).empty());

    testGame->movePiece(2, 4, 0, 2);
    testGame->movePiece(0, 4, 5, 0);
    testGame->movePiece(5, 4, 4, 4);

    testGame->printBoard();

    //If king is in check and no moves will get it out of check, that is checkmate
    CHECK(testGame->checkForCheckMate('B'));
}