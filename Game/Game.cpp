#include <stdexcept>
#include <iostream>
#include "Game.h"

Game::Game(Player &black, Player &white) : black(black), white(white) {
    board = Board();
    black.SetColor(Black);
    white.SetColor(White);
}

std::vector<Move> Game::GetMoves() {
    //TODO
    return std::vector<Move>();
}

bool Game::MakeMove(const Move &move) {
    if (!IsLegal(move))
        throw std::invalid_argument("move");;
    board.Set(move.x1, move.y1, move.color);
    if (move.x2 >= 0 && move.y2 >= 0)
        board.Set(move.x2, move.y2, move.color);
    turn = Color(-turn);
    return true;
}

Color Game::CheckForEndAfter(Move move) {
    bool connected = board.CheckForConnectedAt(move.x1, move.y1, move.color);
    connected |= board.CheckForConnectedAt(move.x2, move.y2, move.color);
    return connected ? move.color : None;
}


Color Game::Play() {
    Color win = None;
    while (win == None) {
        auto move = black.GetMove();
        MakeMove(move);
        win = CheckForEndAfter(move);
        PrintBoard();
        if (win != None) break;
        move = white.GetMove();
        MakeMove(move);
        PrintBoard();
    }
    std::cout << win;
    return win;
}

bool Game::IsLegal(const Move &move) {
    if (move.color != turn) return false;
    if (!board.IsEmpty(move.x1, move.y1))
        return false;
    if (board.IsFirstMoveMade() && (move.x2 >= 0 || move.y2 >= 0) && !board.IsEmpty(move.x2, move.y2))
        return false;
    return true;
}

void Game::PrintBoard() {
    for (char i = 0; i < BOARD_SIZE; ++i) {
        for (char j = 0; j < BOARD_SIZE; ++j) {
            bool w = board.Get(i, j, White);
            bool b = board.Get(i, j, Black);
            char s = w ? 'X' : b ? 'O' : '.';
            std::cout << s;
        }
        std::cout << std::endl;
    }
}

