#include "GameController.hpp"
#include <iostream>
#include <random>

void play(Player& player1, Board& board1, Player& player2, Board& board2, const std::vector<Ship>& fleet) {

    char placement_choice;
    std::cout << "Wie moechten Sie Ihre Flotte platzieren? (r/m - random/manuell): ";
    std::cin >> placement_choice;

    if (placement_choice == 'r') {
        board1.place_fleet_randomly(fleet);
    } else if (placement_choice == 'm') {
        std::cout << "Bitte platzieren Sie Ihre Schiffe manuell.\n";
        board1.place_fleet_manually(fleet);
    } else {
        std::cout << "Ungueltige Eingabe. Flotte wird zufaellig platziert.\n";
        board1.place_fleet_randomly(fleet);
    }

    board2.place_fleet_randomly(fleet);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    bool player1_turn = distrib(gen) == 0;

    while (true) {
        if (player1_turn) {

            player1.print_result_map();

            std::cout << "Spieler 1 ist am Zug.\n";
            player1.performNextMove();

        } else {

            std::cout << "Spieler 2 ist am Zug.\n";
            player2.performNextMove();

            std::cout << board1;
        }

        if (board2.fleet_destroyed()) {
            std::cout << "Spieler 1 hat gewonnen!\n";
            break;
        } else if (board1.fleet_destroyed()) {
            std::cout << "Spieler 2 hat gewonnen!\n";
            break;
        }

        player1_turn = !player1_turn;
    }
}
