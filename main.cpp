#include <iostream>
#include "Game/Game.h"
#include "Random.h"
#include "Interface/ConsoleLogger.h"
#include "Arguments/ArgumentParser.h"
#include "Arguments/EnvironmentCreator.h"
//#include <torch/torch.h>

int main(int argc, const char *argv[]) {
    ArgumentParser args(argc, argv);
    EnvironmentCreator ec(args);
    ec.SetLogger();

    auto p1 = ec.GetPlayer("black");
    auto p2 = ec.GetPlayer("white");
    ConsoleLogger consoleLogger;
    Game game = Game(*p1, *p2, consoleLogger);

    auto result = game.Play();

    return 0;
}
