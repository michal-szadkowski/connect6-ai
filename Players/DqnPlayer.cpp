#include "DqnPlayer.h"

Move DqnPlayer::GetMove(const Board &board, const Move &prevMove) {
    auto first = agent.GetMove(board);
    auto second = StonePos::Empty();

    Board b2 = board;
    b2.PutStone(first, this->GetColor());

    if (b2.GetResult() == Color::None && board.ExpectingFullMove()) {
        second = agent.GetMove(b2);
    }
    AddExperienceFromOwnMove(board, {first, second, this->GetColor()});
    return Move(first, second, this->GetColor());
}

void DqnPlayer::AddExperienceFromOwnMove(const Board &board, const Move &move) {
    Board b2 = board;
    auto first = move.GetFirst();
    auto second = move.GetSecond();
    if (first != StonePos::Empty()) {
        b2.PutStone(first, this->GetColor());
        agent.AddExperience({board, first, b2.GetResult() != Color::None ? 1.0 : 0, b2});

    }
    if (second != StonePos::Empty()) {
        Board b3 = b2;
        b3.PutStone(second, this->GetColor());
        agent.AddExperience({b2, second, b3.GetResult() != Color::None ? 1.0 : 0, b3});
    }
}

