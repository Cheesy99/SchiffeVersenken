#include "Board.hpp"
#include <iostream>
#include <random>
#include <sstream>


Board::Board(size_t dim) : board_dim(dim), grid(dim, std::vector<Field>(dim, Field::WATER)) {
    if (dim < 2 || dim > 10) {
        throw std::invalid_argument("Board dimension must be between 2 and 10.");
    }
}

bool Board::is_valid_position(char col, unsigned char row) const {
    return col >= 'A' && col < 'A' + board_dim && row < board_dim;
}

bool Board::can_place_ship(char col, unsigned char row, size_t length, int orientation) const {
    if (orientation == 1) {
        if (col + length > 'A' + board_dim) {
            std::cout << "Ship would exceed board boundaries.\n";
            return false;
        }
        for (size_t i = 0; i < length; ++i) {
            if (grid[row][col - 'A' + i] == Field::SHIP) {
                std::cout << "Ship overlaps with another ship.\n";
                return false;
            }
        }
    } else {
        if (row + length > board_dim) {
            std::cout << "Ship would exceed board boundaries.\n";
            return false;
        }
        for (size_t i = 0; i < length; ++i) {
            if (grid[row + i][col - 'A'] == Field::SHIP) {
                std::cout << "Ship overlaps with another ship.\n";
                return false;
            }
        }
    }
    return true;
}

void Board::place_ship(char col, unsigned char row, size_t length, int orientation) {
    if (orientation == 1) {
        for (size_t i = 0; i < length; ++i) {
            grid[row][col - 'A' + i] = Field::SHIP;
        }
    } else {
        for (size_t i = 0; i < length; ++i) {
            grid[row + i][col - 'A'] = Field::SHIP;
        }
    }
}

void Board::place_fleet_manually(const std::vector<Ship>& fleet) {
    grid.assign(board_dim, std::vector<Field>(board_dim, Field::WATER));
    for (const auto& ship : fleet) {
        std::cout << "Place ship \"" << ship.type << "\" of length " << ship.length << ":\n";
        bool valid_position = false;

        while (!valid_position) {
            std::string position;
            std::cout << "Enter starting position (e.g., A0): ";
            std::cin >> position;

            if (position.length() != 2) {
                std::cout << "Invalid position format. Please use the format 'A0'.\n";
                continue;
            }

            char col = position[0];
            unsigned char row = position[1] - '0';

            if (!is_valid_position(col, row)) {
                std::cout << "Invalid position. Column must be between A and " << char('A' + board_dim - 1)
                          << ", and row must be between 0 and " << board_dim - 1 << ".\n";
                continue;
            }

            int orientation;
            std::cout << "Horizontal (1) or Vertical (0): ";
            if (!(std::cin >> orientation)) {
                std::cout << "Invalid orientation. Please enter 0 or 1.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (orientation != 0 && orientation != 1) {
                std::cout << "Invalid orientation. Please enter 0 or 1.\n";
                continue;
            }

            if (!can_place_ship(col, row, ship.length, orientation)) {
                continue;
            }

            place_ship(col, row, ship.length, orientation);
            valid_position = true;
        }
    }
}

void Board::place_fleet_randomly(const std::vector<Ship>& fleet) {
    grid.assign(board_dim, std::vector<Field>(board_dim, Field::WATER));
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distrib(0, board_dim - 1);
    std::uniform_int_distribution<> orientation_distrib(0, 1);

    for (const auto& ship : fleet) {
        bool placed = false;
        while (!placed) {
            const int orientation = orientation_distrib(gen);
            const char col = 'A' + distrib(gen);

            if (const unsigned char row = distrib(gen); can_place_ship(col, row, ship.length, orientation)) {
                place_ship(col, row, ship.length, orientation);
                placed = true;
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    std::stringstream ss;

    ss << "  ";
    for (size_t i = 0; i < board.board_dim; ++i) {
        ss << "----";
    }
    ss << "-\n";

    for (size_t i = 0; i < board.board_dim; ++i) {
        ss << "  |";
        for (size_t j = 0; j < board.board_dim; ++j) {
            switch (board.grid[i][j]) {
                case Field::WATER:
                    ss << "   |";
                    break;
                case Field::HIT:
                    ss << " X |";
                    break;
                case Field::SHIP:
                    ss << " S |";
                    break;
            }
        }
        ss << i << "\n";

        ss << "  |";
        for (size_t j = 0; j < board.board_dim; ++j) {
            ss << "----";
        }
        ss << "|\n";
    }

    ss << "   ";
    for (char c = 'A'; c < 'A' + board.board_dim; ++c) {
        ss << " " << c << "  ";
    }
    ss << "\n";

    os << ss.str();
    return os;
}

Field Board::at(char col, unsigned char row) const {
    if (!is_valid_position(col, row)) {
        throw std::out_of_range("Invalid field");
    }
    return grid[row][col - 'A'];
}

void Board::set_ship_manually(char col, unsigned char row) {
    grid[row][col - 'A'] = Field::SHIP;
}


