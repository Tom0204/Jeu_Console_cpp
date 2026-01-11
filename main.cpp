#include <iostream>
#include "Game.h"

void lancerJeu() {
    Game game;
    game.run();
}

int main() {
    int choix = 0;

    do {
        std::cout << "===== Menu =====\n";
        std::cout << "1. Jouer\n";
        std::cout << "2. Exit\n";
        std::cout << "Votre choix : ";
        std::cin >> choix;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide.\n\n";
            continue;
        }

        switch (choix) {
        case 1:
            lancerJeu();
            break;
        case 2:
            std::cout << "Fermeture du programme...\n";
            break;
        default:
            std::cout << "Choix invalide.\n\n";
            break;
        }

    } while (choix != 2);

    return 0;
}