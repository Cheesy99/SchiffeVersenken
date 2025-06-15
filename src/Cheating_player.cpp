#include "Cheating_player.hpp"

CheatingPlayer::CheatingPlayer(ITargetBoard& target_board)
    : Player{ target_board } {}

bool CheatingPlayer::performNextMove() {
    Board* board = dynamic_cast<Board*>(&target_board);
    if (board) {
        size_t dim = board->dim();
        for (unsigned char row = 0; row < dim; ++row) {
            for (char col = 'A'; col < 'A' + dim; ++col) {
                if (board->at(col, row) == Field::SHIP) {
                    board->fire(col, row);
                    return true;
                }
            }
        }
    }
    return false;
}
