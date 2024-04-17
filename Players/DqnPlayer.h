#ifndef CONNECT6_AI_DQNPLAYER_H
#define CONNECT6_AI_DQNPLAYER_H


#include "Player.h"

#include <utility>
#include "../Dqn/Agent.h"
/**
 * Implements deep Q network for playing.
 */
class DqnPlayer final : public Player
{
private:
    Agent agent;
    bool stochastic;
    double accWin = 0;
    int moveCnt = 0;

    /**
     * Creates experience based on board and move and adds it to agents memory.
     * @param board Starting board.
     * @param move Move made in starting position.
     */
    void AddExperienceFromOwnMove(const Board &board, const Move &move);
    /**
     * Calls agent to get single postion to put stone in on bo.ard and updates internal statistics.
     * @param board Board to get position in.
     * @return Position chosen by agent.
     */
    StonePos GetPositionFromBoard(const Board &board);

public:
    /**
     * @param agent Deep Q network agent.
     * @param stochastic If set to true the moves will be choosen based on probabilities returned from network. Otherwise the best one is
     * choosen.
     */
    DqnPlayer(const std::string &name, const Agent &agent, std::shared_ptr<InfoLogger> logger, bool stochastic) :
        Player(name, std::move(logger)), agent(agent), stochastic(stochastic)
    {}


    /**
     * @return Move based on deep Q network policy. If stochastic is true its based on probabilities, max otherwise.
     */
    Move GetMove(const Board &board, const Move &prevMove) override;


    /**
     * @return Average policy reward
     */
    double GetAccWin() { return accWin / moveCnt; };
};


#endif // CONNECT6_AI_DQNPLAYER_H
