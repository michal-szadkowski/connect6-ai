#include "DqnPlayer.h"

Move DqnPlayer::GetMove(const Board &board) {
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
void DqnPlayer::UpdateOnGame(const Move &move, const Board &board) {
    if (currentExperience == nullptr)
        return;
    currentExperience->result = board;
    if (board.GetResult() != Color::None)
        currentExperience->reward = -1;
    agent.AddExperience(*currentExperience);
    currentExperience = nullptr;
}
void DqnPlayer::AddExperienceFromOwnMove(const Board &board, const Move &move) {
    Board b2 = board;
    auto first = move.GetFirst();
    auto second = move.GetSecond();
    if (first != StonePos::Empty()) {
        b2.PutStone(first, this->GetColor());
        if (second == StonePos::Empty()) {
            currentExperience = std::make_shared<Experience>();
            currentExperience->start = board;
            currentExperience->action = first;
        } else {
            agent.AddExperience({board, first, b2.GetResult() != Color::None ? 1.0 : 0, b2});
        }
    }
    if (second != StonePos::Empty()) {
        Board b3 = b2;
        b3.PutStone(second, this->GetColor());
        if (b3.GetResult() != Color::None)
            agent.AddExperience({b2, second, 1.0, b3});
        else {
            currentExperience = std::make_shared<Experience>();
            currentExperience->start = b2;
            currentExperience->action = second;
        }
    }
}

