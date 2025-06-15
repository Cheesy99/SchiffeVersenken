#include "Random_player.hpp"

RandomPlayer::RandomPlayer(ITargetBoard& target_board)
: Player{ target_board }
, gen{std::random_device{}()}
, distrib{0, static_cast<int>(target_board.dim() - 1)} {}

bool RandomPlayer::performNextMove() {
    size_t dim = target_board.dim();
    char col;
    unsigned char row;
    bool shot_successful = false;

    if (already_shot.size() == dim * dim) {
        return false;
    }

    while (true) {
        col = 'A' + distrib(gen);
        row = distrib(gen);

        if (already_shot.find({col, row}) == already_shot.end()) {
            already_shot.insert({col, row});
            break;
        }
    }

    shot_successful = target_board.fire(col, row);
    return shot_successful;
}
