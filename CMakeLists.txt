cmake_minimum_required(VERSION 3.28)
project(connect6_ai)

set(CMAKE_CXX_STANDARD 23)

add_executable(connect6_ai main.cpp
        Game/Board.cpp
        Game/Board.h
        Game/Move.cpp
        Game/Move.h
        Players/Player.cpp
        Players/Player.h
        Game/Game.cpp
        Game/Game.h
        Players/HumanPlayer.cpp
        Players/HumanPlayer.h
        Game/Color.h
)
