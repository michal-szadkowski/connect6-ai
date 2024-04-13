#include "DqnPlayer.h"

Move DqnPlayer::GetMove(const Board &board, const Move &prevMove) {
    auto [first,c1] = agent.GetMove(board);
    accWin += c1;
    StonePos second = StonePos::Empty();
    Board b2 = board;
    b2.PutStone(first, this->GetColor());
    moveCnt++;
    if (b2.GetResult() == Color::None && board.ExpectingFullMove()) {
        auto secMove = agent.GetMove(b2);
        second = secMove.first;
        accWin += secMove.second;
        moveCnt++;
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
        agent.AddExperience(board, first, b2);
    }
    if (second != StonePos::Empty()) {
        Board b3 = b2;
        b3.PutStone(second, this->GetColor());
        agent.AddExperience(b2, second, b3);
    }
}

