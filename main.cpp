#include <iostream>
#include "Game/Game.h"
#include "Random.h"
#include "Arguments/ArgumentParser.h"
#include "Arguments/EnvironmentCreator.h"
//#include <torch/torch.h>

int main(int argc, const char *argv[]) {
    ArgumentParser args(argc, argv);
    EnvironmentCreator ec(args);
    ec.SetLogger();
    int score = 0;
    for (int i = 0; i < ec.GetGameCount(); ++i) {
        auto p1 = ec.GetPlayer("black");
        auto p2 = ec.GetPlayer("white");
        if (i % 2) std::swap(p1, p2);
        Game game = Game(*p1, *p2, *ec.GetGameLogger());
        auto result = game.Play();
        if (result == Color::Black) score += 1;
        if (result == Color::White) score -= 1;
        score = -score;
    }
    if (ec.GetGameCount() % 2) score = -score;
    ec.GetInfoLogger()->WriteInfo("game", std::to_string(score));
    return 0;
}
