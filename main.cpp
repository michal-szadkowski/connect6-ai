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


int main(int argc, const char* argv[])
{
    ArgumentParser args(argc, argv);
    EnvironmentCreator ec(args);
    auto env = ec.Create();
    env->Run();

    // auto q = torch::zeros({3, 3, 5, 5});
    // q[0][0][1][1] = 1;
    // q[0][1][2][1] = 1;
    // q[0][0][3][1] = 1;
    // q[0][2] = torch::ones({5, 5});
    // q[1][0][1][1] = 1;
    // q[1][1][2][1] = 1;
    // q[1][1][3][1] = 1;
    // q[1][2] = torch::ones({5, 5});
    //
    // auto a = q.index({torch::indexing::Slice(0, at::indexing::None), torch::indexing::Slice(0, 2)});
    // std::cout << a;

    return 0;
}
