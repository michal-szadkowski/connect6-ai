#include "PlayEnv.h"
#include "../../Game/Game.h"

#include <format>
#include <utility>


PlayEnv::PlayEnv(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<GameLogger> gameLogger,
                 std::shared_ptr<InfoLogger> infoLogger, int gameCount)
    : p1(p1), p2(p2), gameCount(gameCount), gameLogger(std::move(gameLogger)), infoLogger(std::move(infoLogger)) {}

void PlayEnv::Run()
{
    const auto score = PlayGames();
    infoLogger->WriteInfo("match score", std::format("{}/{}/{}", score.first, (gameCount - score.first - score.second), score.second));
}

std::pair<int, int> PlayEnv::PlayGames() const
{
    auto player1 = p1;
    auto player2 = p2;
    int p1score = 0;
    int p2score = 0;
    for (int i = 0; i < gameCount; ++i)
    {
        auto game = Game(*player1, *player2, gameLogger);
        auto result = game.Play();
        if (result == p1->GetColor())
            p1score += 1;
        if (result == p2->GetColor())
            p2score += 1;
        std::swap(player1, player2);
    }

    return {p1score, p2score};
}
