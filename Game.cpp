//
// Created by joeyt on 9/25/2023.
//

#include "Game.h"

Game* Game::_instance = 0;

Game* Game::instance() {
    if (_instance == 0) {
        _instance = new Game;
    }
    return _instance;
}

Game::Game() {
    _board = new Board;
}