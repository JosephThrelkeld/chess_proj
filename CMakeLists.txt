cmake_minimum_required(VERSION 3.17)
project(chess_proj)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess_proj main.cpp
        Board.cpp
        Game.cpp
        Pieces/Piece.cpp
        Pieces/Piece.h Pieces/Pawn.cpp Pieces/Pawn.h Pieces/Rook.cpp Pieces/Rook.h Pieces/Bishop.cpp Pieces/Bishop.h Pieces/Knight.cpp Pieces/Knight.h Pieces/Queen.cpp Pieces/Queen.h Pieces/King.cpp Pieces/King.h Pieces/AllPieces.h)