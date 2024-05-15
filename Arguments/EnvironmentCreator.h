#ifndef CONNECT6_AI_ENVIRONMENTCREATOR_H
#define CONNECT6_AI_ENVIRONMENTCREATOR_H

#include <memory>
#include <utility>
#include "../Players/DqnPlayer.h"
#include "../Players/HumanPlayer.h"
#include "../Players/MctsPlayer.h"
#include "../Players/Player.h"
#include "ArgumentParser.h"
#include "Environments/Environment.h"


class EnvironmentCreator
{
    ArgumentParser args;
    std::shared_ptr<InfoLogger> infoLogger;
    std::shared_ptr<GameLogger> gameLogger;


    std::shared_ptr<Player> GetPlayer(const std::string &name);
    std::shared_ptr<MctsPlayer> GetMctsPlayer(const std::string &name);
    std::shared_ptr<DqnPlayer> GetDqnPlayer(const std::string &name);
    std::shared_ptr<Environment> CreatePlayEnv();
    std::shared_ptr<Environment> CreateTrainEnv();

    void SetLogger();

public:
    EnvironmentCreator(ArgumentParser &args) : args(std::move(args)) {}
    std::shared_ptr<Environment> Create();
    static void PrintUsage();
};


#endif // CONNECT6_AI_ENVIRONMENTCREATOR_H
