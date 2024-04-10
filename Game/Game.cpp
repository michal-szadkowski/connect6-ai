#include <stdexcept>
#include <iostream>
#include "Game.h"

Game::Game(Player &black, Player &white, GameLogger &logger)
        : black(black), white(white), logger(logger) {
    board = Board();
    black.SetColor(Color::Black);
    white.SetColor(Color::White);
}

Game::Game(Player &black, Player &white, const Board &board, GameLogger &logger)
        : Game(black, white, logger) {
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
        logger.WriteBoard(board, move);
        Player &player = board.GetTurn() == Color::Black ? black : white;
        move = MakePlayerTurn(player, move);
    }
    logger.WriteBoard(board, move);
    return board.GetResult();
}

Move Game::MakePlayerTurn(Player &player, const Move &prevMove) {
    auto move = player.GetMove(board, prevMove);
    history.emplace_back(board, move);
    MakeMove(move);
    return move;
}

bool Game::IsLegal(const Move &move) {
    if (move.GetColor() != board.GetTurn()) return false;
    if (move.GetFirst() == move.GetSecond()) return false;
    if (!board.IsEmpty(move.GetFirst()))
        return false;
    if (!board.ExpectingFullMove() && !move.IsHalf()) {
        return false;
    }
    if (!move.IsHalf() && !board.IsEmpty(move.GetSecond()))
        return false;
    return true;
}