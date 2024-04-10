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


int main(int argc, const char *argv[]) {
//    ArgumentParser args(argc, argv);
//    EnvironmentCreator ec(args);
//    ec.SetLogger();
//    int score = 0;
//    for (int i = 0; i < ec.GetGameCount(); ++i) {
//        auto p1 = ec.GetPlayer("p1");
//        auto p2 = ec.GetPlayer("p2");
//        if (i % 2) std::swap(p1, p2);
//        Game game = Game(*p1, *p2, *ec.GetGameLogger());
//        auto result = game.Play();
//        if (result == Color::Black) score += 1;
//        if (result == Color::White) score -= 1;
//        score = -score;
//    }
//    if (ec.GetGameCount() % 2) score = -score;
//    ec.GetInfoLogger()->WriteInfo("game", std::to_string(score));


    std::shared_ptr<ConsoleLogger> cl = std::make_shared<ConsoleLogger>(0);
    Agent agent(20000);
//    agent.Load("dqnPreTr.pt");

//    agent.Load("./mmCh/t/40800dqnminmax6.pt");

    cl = std::make_shared<ConsoleLogger>(1);


    for (int i = 0; i < 75000; ++i) {
        if (i % 100 == 0)
            cl = std::make_shared<ConsoleLogger>(1);
        else
            cl = std::make_shared<ConsoleLogger>(0);
        double e = 0.85 - (i * 1.0 / (55000)) + 0.05;
        agent.SetEps(e);
        DqnPlayer p1("p1", agent, cl);
        DqnPlayer p2("p2", agent, cl);
        Game game(p1, p2, *cl);
        game.Play();
        std::cout << "\t" << i << "\t" << " eps: " << e << "\t";

        std::cout << agent.Train(35);
        if (i % 400 == 0) {
            agent.Save(std::format("./mmCh/c6/{}dqnminmax6.pt", i));
        }
        std::cout << std::endl;
    }

    cl = std::make_shared<ConsoleLogger>(1);

//    RandomPlayer p1("p1", cl);
//    DqnPlayer p2("p2", agent, cl);
//    Game game(p1, p2, *cl);
//    game.Play();

//    for (int i = 0; i < 30000; ++i) {
//        DqnPlayer p1("p1", agent, cl);
//        DqnPlayer p2("p2", agent, cl);
//        Game game(p1, p2, *cl);
//        game.Play();
//        std::cout << i << "  ";
//
//        std::cout << agent.Train(50) << std::endl;
//        if (i % 1000 == 0)
//            agent.Save(std::format("{}train.pt", i));
//
//    }
//    cl = std::make_shared<ConsoleLogger>(1);
//    agent.Save("mctsTr.pt");

//    MctsPlayer p1("p1", cl, 10000, 1, 1);
//    DqnPlayer p2("p2", agent, cl);
//    Game game(p1, p2, *cl);
//    game.Play();

    return 0;
}
