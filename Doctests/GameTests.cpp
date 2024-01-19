#include "doctest.h"
#include "Game.h"

Game *testGame = Game::instance();

TEST_CASE("Basic Game Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    std::set<std::tuple<unsigned int, unsigned int>> possMoves = testGame->returnPossMoves(1, 1, true);
    CHECK(possMoves.size() == 2);
    CHECK(possMoves.contains({2, 1}));
    CHECK(possMoves.contains({3, 1}));

    testGame->movePiece(1,1,2,1);
    possMoves = testGame->returnPossMoves(2,1, true);

    //Checking moves of empty square should return empty set
    CHECK(testGame->returnPossMoves(1,1, true).empty());
    CHECK(possMoves.size() == 1);
    CHECK(possMoves.contains({3,1}));
}

TEST_CASE("Pawn Tests") {
    CHECK(testGame);

    testGame->setDefaultStart();

    std::set<std::tuple<unsigned int, unsigned int>> possMoves = testGame->returnPossMoves(6, 4, true);
    CHECK(possMoves.size() == 2);
    CHECK(possMoves.contains({5, 4}));
    CHECK(possMoves.contains({4, 4}));

    testGame->movePiece(6,4,4,4);
    possMoves = testGame->returnPossMoves(4,4, true);

    CHECK(possMoves.size() == 1);
    CHECK(possMoves.contains({3,4}));

    testGame->movePiece(1,4,3,4);
    possMoves = testGame->returnPossMoves(4,4, true);

    CHECK(possMoves.empty());

    testGame->movePiece(1,5,3,5);
    possMoves = testGame->returnPossMoves(4,4, true);

    CHECK(possMoves.size() == 1);
    CHECK(possMoves.contains({3,5}));
}