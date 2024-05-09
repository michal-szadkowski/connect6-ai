#ifndef CONNECT6_AI_DQNPLAYER_H
#define CONNECT6_AI_DQNPLAYER_H


#include "Player.h"

#include <utility>
#include "../Dqn/Agent.h"
class DqnPlayer final : public Player
{
private:
    Agent agent;
    bool stochastic;
    double accWin = 0;
    int moveCnt = 0;

        void AddExperienceFromOwnMove(const Board &board, const Move &move);
        StonePos GetPositionFromBoard(const Board &board);

public:
        DqnPlayer(const std::string &name, const Agent &agent, std::shared_ptr<InfoLogger> logger, bool stochastic) :
        Player(name, std::move(logger)), agent(agent), stochastic(stochastic)
    {}


        Move GetMove(const Board &board, const Move &prevMove) override;


        double GetAccWin() { return accWin / moveCnt; };
};


#endif // CONNECT6_AI_DQNPLAYER_H
