cmake_minimum_required(VERSION 3.17)
project(ChessProject)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)
add_executable(ChessProject main.cpp
        GameLogic_lib/ChessPositionAndMovement.h)

include_directories(GameLogic_lib)
add_subdirectory(GameLogic_lib)

target_link_libraries(ChessProject GameLogic_lib)

add_subdirectory(Doctests)