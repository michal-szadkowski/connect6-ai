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
        Game/StonePos.h
        Game/StonePos.cpp
        Players/RandomPlayer.cpp
        Players/RandomPlayer.h
        Mcts/Tree.cpp
        Mcts/Tree.h
        Mcts/Node.cpp
        Mcts/Node.h
        Mcts/Tree.cpp
        Players/MctsPlayer.cpp
        Players/MctsPlayer.h
        Random.cpp
        Random.h
        Interface/Logger.h
        Interface/ConsoleLogger.cpp
        Interface/ConsoleLogger.h
)
