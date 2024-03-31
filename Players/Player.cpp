#include "Player.h"

void Player::SetColor(Color newColor) {
    this->color = newColor;
}

Color Player::GetColor() {
    return this->color;
}

Player::Player(InfoLogger &logger) : logger(logger) {}
