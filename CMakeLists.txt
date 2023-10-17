cmake_minimum_required(VERSION 3.17)
project(chess_proj)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess_proj main.cpp
        Board.cpp
        Game.cpp
        Piece.cpp
        Piece.h Pawn.cpp Pawn.h)