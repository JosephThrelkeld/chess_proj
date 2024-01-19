#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Game.h"

Board *testBoard = new Board();

TEST_CASE("Basic Board Tests") {
    CHECK(testBoard);
    CHECK(!testBoard->getPiece(0, 0));

    testBoard->addPiece(new Pawn('W'), 0, 0);

    CHECK(testBoard->getPiece(0, 0));
    CHECK(testBoard->getPiece(0, 0)->getColor() == 'W');
    CHECK(testBoard->getPiece(0, 0)->getPieceSymbol() == 'P');

    testBoard->clearPiece(0, 0);

    CHECK(!testBoard->getPiece(0, 0));

    testBoard->addPiece(new Pawn('W'), 0, 0);
    testBoard->addPiece(new Pawn('W'), 0, 1);
    testBoard->addPiece(new Pawn('W'), 0, 2);

    CHECK(testBoard->getPiece(0, 0));
    CHECK(testBoard->getPiece(0, 1));
    CHECK(testBoard->getPiece(0, 2));

    testBoard->clearAllPieces();

    CHECK(!testBoard->getPiece(0, 0));
    CHECK(!testBoard->getPiece(0, 1));
    CHECK(!testBoard->getPiece(0, 2));
}