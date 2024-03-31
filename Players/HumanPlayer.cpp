#include <iostream>
#include <format>
#include <utility>
#include "HumanPlayer.h"

Move HumanPlayer::GetMove(const Board &board, const Move &prevMove) {
    int x1 = -1, y1 = -1;
    int x2 = -1, y2 = -1;
    std::string col = this->GetColor() == Color::Black ? "black" : "white";
    logger->WriteInfo(Name(), col + " pos:\nfirst: ");
    std::cin >> x1 >> y1;
    if (board.ExpectingFullMove()) {
        logger->WriteInfo(Name(), "second: ");
        std::cin >> x2 >> y2;
        return {{static_cast<pos_t>(x1),
                 static_cast<pos_t>(y1)},
                {static_cast<pos_t>(x2),
                 static_cast<pos_t>(y2)},
                this->GetColor()};
    }
    return {{static_cast<pos_t>(x1),
             static_cast<pos_t>(y1)},
            this->GetColor()};

}
HumanPlayer::HumanPlayer(std::string name, std::shared_ptr<InfoLogger> logger) :
        Player(std::move(name), std::move(logger)) {}
