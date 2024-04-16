#include "EnvironmentCreator.h"
#include "../Interface/ConsoleLogger.h"

#include <stdexcept>
#include <format>

#include "Environments/DqnTrainEnv.h"
#include "Environments/PlayEnv.h"

void EnvironmentCreator::PrintUsage()
{
    std::cout << R"(
mode=play(default),train 
play parameters:
    games=
    p<1,2>=mcts,dqn,random,human
    p<1,2>-mcts-exp=250000 (default)
    p<1,2>-mcts-sim=5 (default)
    p<1,2>-mcts-expRate=0.43 (default)
    p<1,2>-dqn-inModel=
train parameters:
    startEps=0.5 (default)
    endEps=0.2 (default)
    iterEps=70000 (default)
    memory=100000 (default)
    iters=400000 (default)
    inModel=
    checkPt= 
    outModel=
)";
}

std::shared_ptr<Environment> EnvironmentCreator::CreatePlayEnv()
{
    auto p1 = GetPlayer("p1");
    auto p2 = GetPlayer("p2");
    int gameCount = 1;
    args.TryGetT("games", gameCount);
    return std::make_shared<PlayEnv>(p1, p2, this->gameLogger, this->infoLogger, gameCount);
}

std::shared_ptr<Environment> EnvironmentCreator::CreateTrainEnv()
{
    std::string in, checkPt, out;
    args.TryGetT("inmodel", in);
    args.TryGetT("checkPt", checkPt);
    args.TryGetT("outmodel", out);
    if (out == "")
        throw std::logic_error("No outmodel");

    int mem = 100000;
    args.TryGetT("memory", mem);

    int it = 400000;
    args.TryGetT("iters", it);

    auto env = std::make_shared<DqnTrainEnv>(gameLogger, infoLogger, mem, it);

    env->SetLoad(in);
    env->SetCheckpointDir(checkPt);
    env->SetSave(out);

    double startEps = 0.6, endEps = 0.2;
    int epsIterCount = 70000;
    args.TryGetT("startEps", startEps);
    args.TryGetT("endEps", endEps);
    args.TryGetT("itersEps", epsIterCount);

    env->Eps(startEps, endEps, epsIterCount);

    return env;
}

std::shared_ptr<Environment> EnvironmentCreator::Create()
{
    try
    {
        std::string env = "play";
        args.TryGetT("mode", env);
        if (env == "play")
            return CreatePlayEnv();
        if (env == "train")
            return CreateTrainEnv();
        return nullptr;
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        PrintUsage();
    }
}

std::shared_ptr<Player> EnvironmentCreator::GetPlayer(const std::string& name)
{
    std::string type;
    if (!args.TryGetT(name, type))
        throw std::logic_error("No parameter for player " + name);
    if (type == "mcts") { return GetMctsPlayer(name); }
    if (type == "human") { return std::make_unique<HumanPlayer>(name, infoLogger); }
    if (type == "random") { return std::make_unique<RandomPlayer>(name, infoLogger); }
    throw std::logic_error("Invalid player for " + name);
}

std::shared_ptr<MctsPlayer> EnvironmentCreator::GetMctsPlayer(const std::string& name)
{
    std::string prefix = name + "-mcts-";
    int expCount = 250000;
    int simCount = 5;
    double expRate = 0.43;

    args.TryGetT(prefix + "exp", expCount);
    args.TryGetT(prefix + "sim", simCount);
    args.TryGetT(prefix + "expRate", simCount);
    return std::make_unique<MctsPlayer>(name, infoLogger, expCount, simCount, expRate);
}

void EnvironmentCreator::SetLogger()
{
    int verbosity = 1;
    args.TryGetT("verb", verbosity);

    std::string log = "con";
    args.TryGetT("log", log);
    if (log == "con")
    {
        std::shared_ptr<ConsoleLogger> logger(new ConsoleLogger(verbosity));
        infoLogger = logger;
        gameLogger = logger;
    }
}

