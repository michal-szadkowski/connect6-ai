#include <torch/optim/sgd.h>
#include <torch/types.h>

#include "Arguments/ArgumentParser.h"
#include "Arguments/EnvironmentCreator.h"
#include "Dqn/Agent.h"
#include "Dqn/Network.h"
#include "Game/Game.h"
#include "Interface/ConsoleLogger.h"
#include "Players/DqnPlayer.h"
#include "Random.h"


int main(int argc, const char *argv[])
{
    ArgumentParser args(argc, argv);
    EnvironmentCreator ec(args);
    auto env = ec.Create();
    env->Run();


    return 0;
}
