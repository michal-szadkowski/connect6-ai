#include <stdexcept>
#include <iostream>
#include "Game.h"

Game::Game(Player &black, Player &white) : black(black), white(white) {
    board = Board();
    black.SetColor(Color::Black);
    white.SetColor(Color::White);
}

Game::Game(Player &black, Player &white, const Board &board) : Game(black, white) {
    this->board = board;
}


bool Game::MakeMove(const Move &move) {
    if (!IsLegal(move))
        throw std::invalid_argument("move");
    board.Set(move.GetFirst(), move.GetColor());
    if (move.GetSecond() != StonePos::Empty())
        board.Set(move.GetSecond(), move.GetColor());
    return true;
}


Color Game::CheckForEndAfter(Move move) {
    Color col = board.CheckWinAfter(move.GetFirst(), move.GetColor());
    if (col == Color::None && move.GetSecond() != StonePos::Empty())
        col = board.CheckWinAfter(move.GetSecond(), move.GetColor());
    return col;
}


Color Game::Play() {
    if (result != Color::None) throw std::exception();
    Move move = Move(StonePos::Empty(), StonePos::Empty(), Color::None);
    while (result == Color::None) {
        Player &p = board.GetTurn() == Color::Black ? black : white;
        move = MakePlayerTurn(p, move);
    }
    return result;
}
Move Game::MakePlayerTurn(Player &player, const Move &prevMove) {
    auto move = player.GetMove(board, prevMove);
    MakeMove(move);
    result = CheckForEndAfter(move);
//    PrintBoard();
    return move;
}

bool Game::IsLegal(const Move &move) {
    if (move.GetColor() != board.GetTurn()) return false;
    if (move.GetFirst() == move.GetSecond()) return false;
    if (!board.IsEmpty(move.GetFirst()))
        return false;
    if (move.IsHalf()) {
        if ((board.ExpectingHalfMove() != 0))
            return false;
    } else if (!board.IsEmpty(move.GetSecond()))
        return false;
    return true;
}

void Game::PrintBoard() {
    for (char i = 0; i < BOARD_SIZE; ++i) {
        for (char j = 0; j < BOARD_SIZE; ++j) {
            bool w = board.Get({i, j}, Color::White);
            bool b = board.Get({i, j}, Color::Black);
            char s = w ? 'X' : b ? 'O' : '.';
            std::cout << s;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}