#ifndef DQNTRAINENV_H
#define DQNTRAINENV_H
#include <memory>

#include "../../Dqn/Agent.h"
#include "../../Interface/GameLogger.h"
#include "../../Interface/InfoLogger.h"
#include "Environment.h"

class DqnTrainEnv final : public Environment
{
    std::shared_ptr<GameLogger> gameLogger{};
    std::shared_ptr<InfoLogger> infoLogger{};
    Agent agentCurrent;
    int iterations;

    std::string load, checkpoint, save;

    /**
     * Tries to load model from loadPath
     */
    void LoadModel();

    /**
     * Tries to save model after iteration
     * @param i Iteration
     */
    void CheckPointModel(int i);

    /**
     * Saves model after all iterations
     */
    void SaveModel();

    /**
     * Plays games in threads and sums threir results
     * @param gamesPerTh Amount of games played per thread
     * @param threads Amount of threads
     * @param stochastic Whtether the games should be stochastic
     * @param a1 First agent
     * @param a2 Second agent
     * @return Win count of first and second agent
     */
    std::pair<int, int> PlayGames(int gamesPerTh, int threads, bool stochastic, Agent &a1, Agent &a2);
    /**
     * Prints the results of games
     * @param results Wins of first and second player
     * @param total Total games played, altough draw is unusual it is possible and it is not contained in results
     */
    void PrintResults(const std::pair<int, int> &results, int total);

    /**
     * Plays game and prints it
     * @param a1 First agent
     * @param a2 Second agent
     */
    void PlayGameAndPrint(Agent &a1, Agent &a2);

public:
    /**
     * Creates environment for training dqn
     * @param agentMemory Memory of agents
     * @param iterations Training loop iterations
     */
    DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations);

    /**
     * Launches training loop. Each loop consists of playing 1250 games against self, training network for 1500 batches and playing 250
     * evaluating games against previous self. If new agent wins at least 130 games it advances as winner. If it wins at most 120 games it
     * is discarded.
     */
    void Run() override;

    /**
     * Sets path to model file to load at the beggining of training loop
     * @param loadPath Path to file containing model to load.
     */
    void SetLoad(std::string loadPath);

    /**
     * Sets path to checkpoint model after every 5 loops
     * @param chPath Path for checkpoint. Can be in format path/filenameprefix
     */
    void SetCheckpointDir(std::string chPath);
    /**
     * Sets path to file for saving model after all loops.
     * @param outPath Path to file with .pt extension
     */
    void SetSave(std::string outPath);
};


#endif // DQNTRAINENV_H
