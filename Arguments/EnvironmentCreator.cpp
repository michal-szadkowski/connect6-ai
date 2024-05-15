#include "EnvironmentCreator.h"

#include <stdexcept>

#include "../Interface/ConsoleLogger.h"
#include "../Players/RandomPlayer.h"
#include "Environments/DqnTrainEnv.h"
#include "Environments/PlayEnv.h"

void EnvironmentCreator::PrintUsage()
{
    std::cout << R"(
mode=play(default),train 
play parameters:
    games=1,2...
    p<1,2>=mcts,dqn,random,human
    p<1,2>-mcts-exp=250000 (default)
    p<1,2>-mcts-sim=5 (default)
    p<1,2>-mcts-expRate=0.43 (default)
    p<1,2>-dqn-inmodel=
    log=con(default),file
train parameters:
    memory=150000 (default)
    iters=400000 (default)
    inmodel=
    checkPt= 
    outmodel=
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

    int mem = 2000000;
    args.TryGetT("memory", mem);

    int it = 100000;
    args.TryGetT("iters", it);

    auto env = std::make_shared<DqnTrainEnv>(gameLogger, infoLogger, mem, it);

    env->SetLoad(in);
    env->SetCheckpointDir(checkPt);
    env->SetSave(out);

    return env;
}

std::shared_ptr<Environment> EnvironmentCreator::Create()
{
    try
    {
        SetLogger();
        std::string env = "play";
        args.TryGetT("mode", env);
        if (env == "play")
            return CreatePlayEnv();
        if (env == "train")
            return CreateTrainEnv();
        return nullptr;
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
        PrintUsage();
    }
    return nullptr;
}

std::shared_ptr<Player> EnvironmentCreator::GetPlayer(const std::string &name)
{
    std::string type;
    if (!args.TryGetT(name, type))
        throw std::logic_error("No parameter for player " + name);
    if (type == "mcts")
    {
        return GetMctsPlayer(name);
    }
    if (type == "human")
    {
        return std::make_unique<HumanPlayer>(name, infoLogger);
    }
    if (type == "dqn")
    {
        return GetDqnPlayer(name);
    }
    if (type == "random")
    {
        return std::make_unique<RandomPlayer>(name, infoLogger);
    }
    throw std::logic_error("Invalid player for " + name);
}

std::shared_ptr<MctsPlayer> EnvironmentCreator::GetMctsPlayer(const std::string &name)
{
    std::string prefix = name + "-mcts-";
    int expCount = 350000;
    int simCount = 5;
    double expRate = 0.43;

    args.TryGetT(prefix + "exp", expCount);
    args.TryGetT(prefix + "sim", simCount);
    args.TryGetT(prefix + "expRate", simCount);
    return std::make_unique<MctsPlayer>(name, infoLogger, expCount, simCount, expRate);
}

std::shared_ptr<DqnPlayer> EnvironmentCreator::GetDqnPlayer(const std::string &name)
{
    std::string prefix = name + "-dqn-";

    std::string in;
    args.TryGetT(prefix + "inmodel", in);
    if (in == "")
        throw std::logic_error("No inmodel");

    Agent agent(0);
    agent.Load(in);
    return std::make_shared<DqnPlayer>(name, agent, infoLogger, false);
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
    if (log == "file")
    {
        std::shared_ptr<FileLogger> logger(new FileLogger(verbosity));
        infoLogger = logger;
        gameLogger = logger;
    }
}
