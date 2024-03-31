#include "Player.h"

#include <utility>

void Player::SetColor(Color newColor) {
    this->color = newColor;
}

Color Player::GetColor() {
    return this->color;
}

Player::Player(std::string name, std::shared_ptr<InfoLogger> logger) : name(std::move(name)),
                                                                       logger(std::move(logger)) {}
