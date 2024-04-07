#ifndef CONNECT6_AI_DQNPLAYER_H
#define CONNECT6_AI_DQNPLAYER_H


#include "Player.h"

#include <utility>
#include "../Dqn/Agent.h"

class DqnPlayer : public Player {
private:
    Agent &agent;
    std::shared_ptr<Experience> currentExperience;
    void AddExperienceFromOwnMove(const Board &board, const Move &move);
public:
    DqnPlayer(const std::string &name, Agent &agent, std::shared_ptr<InfoLogger> logger) :
            Player(name, std::move(logger)), agent(agent) {}
    Move GetMove(const Board &board) override;
    void UpdateOnGame(const Move &move, const Board &board) override;
    void Train() { agent.Train(100); }
};


#endif //CONNECT6_AI_DQNPLAYER_H
