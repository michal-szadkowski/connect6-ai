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


void Game::MakeMove(const Move &move) {
    if (!IsLegal(move))
        throw std::invalid_argument("move");
    auto r = board.PutStone(move.GetFirst(), move.GetColor());
    if (move.GetSecond() != StonePos::Empty() && r == Color::None)
        board.PutStone(move.GetSecond(), move.GetColor());
}

Color Game::Play() {
    if (board.GetResult() != Color::None) throw std::logic_error("can't start game with result");
    Move move = Move(StonePos::Empty(), StonePos::Empty(), Color::None);
    while (board.GetResult() == Color::None) {
        Player &p = board.GetTurn() == Color::Black ? black : white;
        move = MakePlayerTurn(p, move);
    }
    return board.GetResult();
}
Move Game::MakePlayerTurn(Player &player, const Move &prevMove) {
    auto move = player.GetMove(board, prevMove);
    MakeMove(move);
    return move;
}

bool Game::IsLegal(const Move &move) {
    if (move.GetColor() != board.GetTurn()) return false;
    if (move.GetFirst() == move.GetSecond()) return false;
    if (!board.IsEmpty(move.GetFirst()))
        return false;
    if (move.IsHalf()) {
        if (board.ExpectingFullMove())
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