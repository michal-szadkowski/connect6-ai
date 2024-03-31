#ifndef CONNECT6_AI_ENVIRONMENTCREATOR_H
#define CONNECT6_AI_ENVIRONMENTCREATOR_H


#include <memory>
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
    void SetLogger();
    std::unique_ptr<Player> GetPlayer(const std::string &name);

    MctsPlayer GetMctsPlayer(std::string name);
    RandomPlayer GetRandomPlayer(std::string name);


    void PrintUsage();
};


#endif //CONNECT6_AI_ENVIRONMENTCREATOR_H
