#ifndef CONNECT6_AI_PLAYER_H
#define CONNECT6_AI_PLAYER_H

#include <memory>
#include "../Game/Board.h"
#include "../Game/Move.h"
#include "../Interface/InfoLogger.h"

class Player
{
private:
    std::string name;
    Color color = Color::None;

protected:
    std::shared_ptr<InfoLogger> logger;

public:
        Player(std::string name, std::shared_ptr<InfoLogger> logger);
        std::string Name();

        void SetColor(Color newColor);
        Color GetColor();

        virtual Move GetMove(const Board &board, const Move &prevMove) = 0;
    virtual ~Player() = default;
};

#endif // CONNECT6_AI_PLAYER_H
