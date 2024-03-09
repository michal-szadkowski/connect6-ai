#include <stdexcept>
#include <iostream>
#include "Game.h"

Game::Game(Player &black, Player &white) : black(black), white(white) {
    board = Board();
    black.SetColor(Color::Black);
    white.SetColor(Color::White);
}

std::vector<Move> Game::GetMoves() {
    //TODO
    return std::vector<Move>();
}

bool Game::MakeMove(const Move &move) {
    if (!IsLegal(move))
        throw std::invalid_argument("move");
    board.Set(move.first, move.color);
    if (move.second != StonePos::Empty())
        board.Set(move.second, move.color);
    turn = static_cast<Color>(-static_cast<int> (turn));
    return true;
}

Color Game::CheckForEndAfter(Move move) {
    bool connected = board.CheckForConnectedAt(move.first, move.color);
    if (move.second != StonePos::Empty())
        connected |= board.CheckForConnectedAt(move.second, move.color);
    return connected ? move.color : Color::None;
}


Color Game::Play() {
    Color win = Color::None;
    Move move = Move(StonePos::Empty(), StonePos::Empty(), Color::None);
    while (win == Color::None) {
        move = black.GetMove(board, move);
        MakeMove(move);
        win = CheckForEndAfter(move);
        PrintBoard();
        if (win != Color::None) break;
        move = white.GetMove(board, move);
        MakeMove(move);
        PrintBoard();
    }
    std::cout << (win == Color::Black ? "black " : "white ") << "wins";
    return win;
}

bool Game::IsLegal(const Move &move) {
    if (move.color != turn) return false;
    if (move.first == move.second)return false;
    if (!board.IsEmpty(move.first))
        return false;
    if (move.second == StonePos::Empty()) {
        if ((board.StonesPlacedCount() != 0))
            return false;
    } else if (!board.IsEmpty(move.second))
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
}

