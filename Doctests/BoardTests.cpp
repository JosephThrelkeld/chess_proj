#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.h"

Game* myGame = Game::instance();

TEST_CASE("testing the board") {
    CHECK(myGame);
}