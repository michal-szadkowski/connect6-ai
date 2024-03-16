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
    board.Set(move.GetFirst(), move.GetColor());
    if (move.GetSecond() != StonePos::Empty())
        board.Set(move.GetSecond(), move.GetColor());
    ChangeTurn();
    return true;
}


Color Game::CheckForEndAfter(Move move) {
    Color col = board.CheckWinAfter(move.GetFirst(), move.GetColor());
    if (col == Color::None && move.GetSecond() != StonePos::Empty())
        col = board.CheckWinAfter(move.GetSecond(), move.GetColor());
    return col;
}


Color Game::Play() {
    Color win = Color::None;
    Move move = Move(StonePos::Empty(), StonePos::Empty(), Color::None);
    while (win == Color::None || win == Color::Draw) {
        move = black.GetMove(board, move);
        MakeMove(move);
        win = CheckForEndAfter(move);
        PrintBoard();
        if (win != Color::None) break;
        move = white.GetMove(board, move);
        MakeMove(move);
        win = CheckForEndAfter(move);
        PrintBoard();
    }
    if (win == Color::Black) std::cout << "black";
    else if (win == Color::White) std::cout << "white";
    else if (win == Color::Draw)std::cout << "draw";
    return win;
}

bool Game::IsLegal(const Move &move) {
    if (move.GetColor() != turn) return false;
    if (move.GetFirst() == move.GetSecond())return false;
    if (!board.IsEmpty(move.GetFirst()))
        return false;
    if (move.IsHalf()) {
        if ((board.StonesPlacedCount() != 0))
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

void Game::ChangeTurn() {
    if (turn == Color::White)turn = Color::Black;
    else if (turn == Color::Black) turn = Color::White;
}

