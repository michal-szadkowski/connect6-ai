#ifndef CONNECT6_AI_DQNPLAYER_H
#define CONNECT6_AI_DQNPLAYER_H


#include "Player.h"

#include <utility>
#include "../Dqn/Agent.h"

class DqnPlayer : public Player {
private:
    Agent &agent;

    double accWin = 0;
    int moveCnt = 0;
    void AddExperienceFromOwnMove(const Board &board, const Move &move);

public:
    DqnPlayer(const std::string &name, Agent &agent,
              std::shared_ptr<InfoLogger> logger) : Player(name, std::move(logger)), agent(agent) {
    }
    Move GetMove(const Board &board, const Move &prevMove) override;
    double GetAccWin() { return accWin / moveCnt; };
};


#endif //CONNECT6_AI_DQNPLAYER_H