#ifndef CONNECT6_AI_ENVIRONMENTCREATOR_H
#define CONNECT6_AI_ENVIRONMENTCREATOR_H


#include <memory>
#include <utility>
#include "../Players/Player.h"
#include "ArgumentParser.h"
#include "../Players/HumanPlayer.h"
#include "../Players/MctsPlayer.h"
#include "../Players/RandomPlayer.h"

class EnvironmentCreator {
    ArgumentParser args;
    std::shared_ptr<InfoLogger> infoLogger;
    std::shared_ptr<GameLogger> gameLogger;
public:
    EnvironmentCreator(ArgumentParser &args) : args(std::move(args)) {}

    void SetLogger();
    std::unique_ptr<Player> GetPlayer(const std::string &name);
    std::shared_ptr<GameLogger> GetGameLogger() { return gameLogger; }
    std::shared_ptr<InfoLogger> GetInfoLogger() { return infoLogger; }

    std::unique_ptr<MctsPlayer> GetMctsPlayer(const std::string &name);

    int GetGameCount();

    void PrintUsage();
};


#endif //CONNECT6_AI_ENVIRONMENTCREATOR_H
