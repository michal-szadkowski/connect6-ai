cmake_minimum_required(VERSION 3.22)
project(connect6_ai)

set(CMAKE_CUDA_ARCHITECTURES 61)
set(CMAKE_CUDA_COMPILER /opt/cuda/bin/nvcc)
find_package(Torch REQUIRED)
set(CMAKE_CXX_STANDARD 23)

add_executable(connect6_ai main.cpp
        Game/Board.cpp
        Game/Board.h
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
        Interface/GameLogger.h
        Interface/ConsoleLogger.cpp
        Interface/ConsoleLogger.h
        Arguments/ArgumentParser.cpp
        Arguments/ArgumentParser.h
        Arguments/EnvironmentCreator.cpp
        Arguments/EnvironmentCreator.h
        Interface/InfoLogger.h
        Players/DqnPlayer.cpp
        Players/DqnPlayer.h
        Dqn/Agent.cpp
        Dqn/Agent.h
        Dqn/ReplayMemory.cpp
        Dqn/ReplayMemory.h
        Dqn/Network.h
        Arguments/Environments/Environment.h
        Arguments/Environments/PlayEnv.cpp
        Arguments/Environments/PlayEnv.h
        Arguments/Environments/DqnTrainEnv.cpp
        Arguments/Environments/DqnTrainEnv.h
        Interface/NoLogger.h
        Interface/FileLogger.cpp
        Interface/FileLogger.h
)
target_link_libraries(connect6_ai "${TORCH_LIBRARIES}")
target_include_directories(connect6_ai PRIVATE ${TORCH_LIBRARIES})
