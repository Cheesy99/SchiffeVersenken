#include "Human_player.hpp"
#include <iostream>
#include <string>

HumanPlayer::HumanPlayer(ITargetBoard& target_board)
    : Player{ target_board } {}

bool HumanPlayer::performNextMove() {
    char col = 0;
    unsigned char row = 0;
    bool shot_successful = false;
    bool valid_input = false;

    while (!valid_input) {
        std::cout << "Wo wollen sie angreifen? (Zaehlend von A und 0)\n";
        std::cout << "Eingabeformat: <Spalte><Zeile>, zum Beispiel 'A2':\n";
        std::cout << ">> ";

        std::string input;
        std::cin >> input;

        if (input.length() != 2) {
            std::cout << "Eingabe ist ungueltig\n";
            continue;
        }

        col = input[0];
        row = input[1] - '0';

        if (col < 'A' || col >= 'A' + target_board.dim() || row < 0 || row >= target_board.dim()) {
            std::cout << "Eingabe ist ungueltig\n";
            continue;
        }

        valid_input = true;
    }

    shot_successful = target_board.fire(col, row);

    if (shot_successful) {
        std::cout << "Alles klar.\n";
        std::cout << "Treffer auf " << col << row << "!\n";
    } else {
        std::cout << "Alles klar.\n";
        std::cout << "Kein Treffer auf " << col << row << "!\n";
    }

    return shot_successful;
}