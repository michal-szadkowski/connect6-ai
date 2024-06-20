#include "DqnPlayer.h"

#include "../Random.h"

Move DqnPlayer::GetMove(const Board &board, const Move &prevMove)
{
    auto p1 = GetPositionFromBoard(board);
    Board b2 = board;
    b2.PutStone(p1, this->GetColor());

    auto p2 = StonePos::Empty();
    if (b2.GetResult() == Color::None && board.ExpectingFullMove())
    {
        p2 = GetPositionFromBoard(b2);
    }
    if (rememberActions)
        AddExperienceFromOwnMove(board, {p1, p2, this->GetColor()});
    return {p1, p2, this->GetColor()};
}

StonePos DqnPlayer::GetPositionFromBoard(const Board &board)
{
    auto [result2, c] = agent.GetMove(board, eps);
    avgWin += moveCnt * avgWin + c;
    moveCnt += 1;
    avgWin /= moveCnt;

    return result2;
}

void DqnPlayer::AddExperienceFromOwnMove(const Board &board, const Move &move)
{
    Board b2 = board;
    auto first = move.GetFirst();
    auto second = move.GetSecond();
    if (first != StonePos::Empty())
    {
        b2.PutStone(first, move.GetColor());
        agent.AddExperience(board, first, b2);
    }
    if (second != StonePos::Empty())
    {
        Board b3 = b2;
        b3.PutStone(second, move.GetColor());
        agent.AddExperience(b2, second, b3);
    }
}
