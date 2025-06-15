#include "Player.hpp"
#include <iostream>

Player::Player(ITargetBoard& target_board) : target_board(target_board) {}

Player::~Player() {}

void Player::print_result_map() const {
    size_t dim = target_board.dim();

    std::cout << "  ";
    for (size_t i = 0; i < dim; ++i) {
        std::cout << "----";
    }
    std::cout << "-\n";

    for (size_t i = 0; i < dim; ++i) {
        std::cout << "  |";
        for (size_t j = 0; j < dim; ++j) {
            char col = 'A' + j;
            unsigned char row = i;
            try {
                Field field = static_cast<Board&>(target_board).at(col, row);
                switch (field) {
                    case Field::WATER:
                        std::cout << "   |";
                        break;
                    case Field::HIT:
                        std::cout << " X |";
                        break;
                    case Field::SHIP:
                        std::cout << " ~ |";
                        break;
                }
            } catch (const std::out_of_range& e) {
                std::cout << "   |";
            }
        }
        std::cout << i << "\n";

        std::cout << "  |";
        for (size_t j = 0; j < dim; ++j) {
            std::cout << "----";
        }
        std::cout << "|\n";
    }

    std::cout << "   ";
    for (char c = 'A'; c < 'A' + dim; ++c) {
        std::cout << " " << c << "  ";
    }
    std::cout << "\n";
}
