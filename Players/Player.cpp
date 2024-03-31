#include "Player.h"

#include <utility>

void Player::SetColor(Color newColor) {
    this->color = newColor;
}

Color Player::GetColor() {
    return this->color;
}

Player::Player(std::shared_ptr<InfoLogger> logger) : logger(std::move(logger)) {}
