#include <iostream>
#include <format>
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(Logger &logger) : logger(logger) {

}


Move HumanPlayer::GetMove(const Board &board, const Move &prevMove) {
    int x1 = -1, y1 = -1;
    int x2 = -1, y2 = -1;
    logger.WriteBoard(board, prevMove);
    std::string col = this->GetColor() == Color::Black ? "black" : "white";
    std::cout << col << " pos:\nfirst:\n";
    std::cin >> x1 >> y1;
    if (board.ExpectingFullMove()) {
        std::cout << "second: \n";
        std::cin >> x2 >> y2;
        return {{static_cast<char>(x1),
                 static_cast<char>(y1)},
                {static_cast<char>(x2),
                 static_cast<char>(y2)},
                this->GetColor()};
    }
    return {{static_cast<char>(x1),
             static_cast<char>(y1)},
            this->GetColor()};

}
