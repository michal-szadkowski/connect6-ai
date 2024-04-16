#include <iostream>
#include "Game/Game.h"
#include "Arguments/ArgumentParser.h"
#include "Arguments/EnvironmentCreator.h"
#include "Dqn/Network.h"
#include "Dqn/Agent.h"
#include "Players/DqnPlayer.h"
#include "Interface/ConsoleLogger.h"
#include <torch/types.h>
#include <torch/optim/sgd.h>


int main(int argc, const char* argv[])
{
    ArgumentParser args(argc, argv);
    EnvironmentCreator ec(args);
    ec.SetLogger();

    auto env = ec.Create();
    env->Run();


    return 0;
}
