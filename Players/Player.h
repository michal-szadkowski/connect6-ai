#ifndef CONNECT6_AI_PLAYER_H
#define CONNECT6_AI_PLAYER_H


#include "../Game/Move.h"
#include "../Game/Board.h"

class Player {
private:
    Color color = Color::None;
public:
    void SetColor(Color newColor);
    Color GetColor();
    virtual Move GetMove(const Board &board, const Move &prevMove) = 0;
};


#endif //CONNECT6_AI_PLAYER_H
