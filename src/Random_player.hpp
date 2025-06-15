#pragma once

#include "Player.hpp"
#include <random>
#include <set>

class RandomPlayer : public Player {
  public:
    explicit RandomPlayer(ITargetBoard& target_board);
    bool performNextMove() override;

private:
    std::set<std::pair<char, unsigned char>> already_shot;
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib;
};
