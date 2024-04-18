#include "HumanPlayer.h"
#include <format>
#include <iostream>
#include <utility>

StonePos HumanPlayer::RequestMove(const Board &board, const StonePos &prev)
{
    int x = -1, y = -1;
    StonePos pos = StonePos::Empty();
    while (true)
    {
        logger->WriteInfo(Name(), "Please input position:");
        logger->WriteInfo(Name(), "Row:");
        std::cin >> x;
        logger->WriteInfo(Name(), "Column:");
        std::cin >> y;
        pos = {static_cast<pos_t>(x), static_cast<pos_t>(y)};
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y > BOARD_SIZE || !board.IsEmpty(pos) || pos == prev)
        {
            logger->WriteInfo(Name(), "Invalid move!");
            continue;
        }
        return pos;
    }
}

Move HumanPlayer::GetMove(const Board &board, const Move &prevMove)
{
    StonePos first = RequestMove(board, StonePos::Empty());
    if (board.ExpectingFullMove())
    {
        StonePos second = RequestMove(board, first);
        return {first, second, this->GetColor()};
    }
    return {first, this->GetColor()};
}
HumanPlayer::HumanPlayer(const std::string &name, std::shared_ptr<InfoLogger> logger) : Player(name, std::move(logger)) {}
