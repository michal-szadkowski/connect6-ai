#ifndef CONNECT6_AI_PLAYER_H
#define CONNECT6_AI_PLAYER_H


#include "../Game/Move.h"

class Player {
private:
    Color color;
public:
    void SetColor(Color colorToSet);
    Color GetColor();
    virtual Move GetMove() = 0;
};


#endif //CONNECT6_AI_PLAYER_H
