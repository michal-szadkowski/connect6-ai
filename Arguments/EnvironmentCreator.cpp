#include "EnvironmentCreator.h"
#include "../Players/HumanPlayer.h"
#include "../Interface/ConsoleLogger.h"

#include <utility>
#include <stdexcept>

void EnvironmentCreator::PrintUsage() {

}
std::unique_ptr<Player> EnvironmentCreator::GetPlayer(const std::string &name) {
    std::string type;
    if (!args.TryGet(name, type)) throw std::logic_error("No parameter for player " + name);
    if (type == "mcts") {

    } else if (type == "human") {
        return std::make_unique<HumanPlayer>(*infoLogger);
    } else if (type == "random") {
    }
    throw std::logic_error("Invalid player for " + name);
}
MctsPlayer EnvironmentCreator::GetMctsPlayer(std::string name) {
    ;
}

void EnvironmentCreator::SetLogger() {
    std::string log = "con";
    args.TryGet("log", log);
    if (log == "con") {
        std::shared_ptr<ConsoleLogger> logger(new ConsoleLogger());
        infoLogger = logger;
        gameLogger = logger;
    }
}
