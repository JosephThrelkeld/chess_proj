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

Board Game::gameBoard() {
    return _board;
}