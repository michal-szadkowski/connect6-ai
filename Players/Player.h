#ifndef CONNECT6_AI_PLAYER_H
#define CONNECT6_AI_PLAYER_H


#include "../Game/Move.h"
#include "../Game/Board.h"
#include "../Interface/InfoLogger.h"

class Player {
private:
    Color color = Color::None;
protected:
    InfoLogger &logger;
public:
    Player(InfoLogger &logger);
    void SetColor(Color newColor);
    Color GetColor();
    virtual Move GetMove(const Board &board, const Move &prevMove) = 0;
    virtual ~Player() = default;
};


#endif //CONNECT6_AI_PLAYER_H
