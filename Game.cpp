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
    this->setBackRank(0, 'b');
    this->setFrontRank(1,'b');
    this->setBackRank(7, 'w');
    this->setFrontRank(6,'w');
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