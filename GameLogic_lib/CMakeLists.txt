project(GameLogic)

include_directories(Pieces)

set(HEADER_FILES
        Board.h
        Game.h
        )

set(PIECE_HEADER_FILES
        Pieces/AllPieces.h
        Pieces/Bishop.h
        Pieces/King.h
        Pieces/Knight.h
        Pieces/Pawn.h
        Pieces/Piece.h
        Pieces/Piece.h
        Pieces/Queen.h
        Pieces/Rook.h
        )

set(SOURCE_FILES
        Board.cpp
        Game.cpp
        )

set(PIECE_SOURCE_FILES
        Pieces/Bishop.cpp
        Pieces/King.cpp
        Pieces/Knight.cpp
        Pieces/Pawn.cpp
        Pieces/Piece.cpp
        Pieces/Piece.cpp
        Pieces/Queen.cpp
        Pieces/Rook.cpp
        )

add_library(GameLogic_lib STATIC ${SOURCE_FILES} ${PIECE_SOURCE_FILES} ${HEADER_FILES} ${PIECE_HEADER_FILES})




