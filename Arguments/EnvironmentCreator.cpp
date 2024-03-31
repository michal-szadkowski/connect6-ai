#include "EnvironmentCreator.h"
#include "../Players/HumanPlayer.h"
#include "../Interface/ConsoleLogger.h"

#include <utility>
#include <stdexcept>
#include <format>

void EnvironmentCreator::PrintUsage() {

}
std::unique_ptr<Player> EnvironmentCreator::GetPlayer(const std::string &name) {
    std::string type;
    if (!args.TryGet(name, type)) throw std::logic_error("No parameter for player " + name);
    if (type == "mcts") {
        return GetMctsPlayer(name);
    } else if (type == "human") {
        return std::make_unique<HumanPlayer>(infoLogger);
    } else if (type == "random") {
        return std::make_unique<RandomPlayer>(infoLogger);
    }
    throw std::logic_error("Invalid player for " + name);
}
std::unique_ptr<MctsPlayer> EnvironmentCreator::GetMctsPlayer(const std::string &name) {
    std::string prefix = name + "-mcts-";
    int expCount = 250000;
    int simCount = 5;
    double expRate = 0.4;

    std::string str;
    if (args.TryGet(prefix + "exp", str)) {
        expCount = std::stoi(str);
    }
    if (args.TryGet(prefix + "sim", str)) {
        simCount = std::stoi(str);
    }
    if (args.TryGet(prefix + "expR", str)) {
        expRate = std::stod(str);
    }
    return std::make_unique<MctsPlayer>(infoLogger, expCount, simCount, expRate);
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
