#ifndef CONNECT6_AI_ENVIRONMENTCREATOR_H
#define CONNECT6_AI_ENVIRONMENTCREATOR_H


#include <memory>
#include <utility>
#include "../Players/Player.h"
#include "ArgumentParser.h"
#include "../Players/DqnPlayer.h"
#include "../Players/HumanPlayer.h"
#include "../Players/MctsPlayer.h"
#include "../Players/RandomPlayer.h"
#include "Environments/Environment.h"


/**
 * Reads program arguments and creates exectution environment
 */
class EnvironmentCreator
{
    ArgumentParser args;
    std::shared_ptr<InfoLogger> infoLogger;
    std::shared_ptr<GameLogger> gameLogger;


    /**
     * Creates player with type from arguments
     * @param name p1 or p2
     * @return Created player
     */
    std::shared_ptr<Player> GetPlayer(const std::string& name);
    /**
     * Creates mcts player
     */
    std::shared_ptr<MctsPlayer> GetMctsPlayer(const std::string& name);
    /**
     * Creates dqn player
     */
    std::shared_ptr<DqnPlayer> GetDqnPlayer(const std::string& name);

    /**
     * Creates playing environment with players specified by arguments
     */
    std::shared_ptr<Environment> CreatePlayEnv();
    /**
     * Creates training environments with input model, checkpoints and save model and iterations
     */
    std::shared_ptr<Environment> CreateTrainEnv();

    /**
     * Reads logger parameters and creates loggers
     */
    void SetLogger();

public:
    /**
     * Creates creator with given arguments
     */
    EnvironmentCreator(ArgumentParser& args) : args(std::move(args)) {}


    /**
     * Creates environment specified by arguments
     */
    std::shared_ptr<Environment> Create();


    /**
     * Prints usage of program
     */
    void PrintUsage();
};


#endif //CONNECT6_AI_ENVIRONMENTCREATOR_H
