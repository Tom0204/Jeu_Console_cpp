#include "UIManager.h"
#include "Game.h"
#include <iostream>
#include <limits>

int UIManager::gererChoix( const Game& game, Phase phase ) {
    afficherActions( phase );
    std::cout << "Votre choix (0-5) ? ";

    int choix;
    std::cin >> choix;

    if ( choix == 0 ) {
        std::cout << "\nMerci d'avoir joue !\n";
        exit(0);
    }

    return (choix >= 1 && choix <= 5) ? choix : 1;
}

void UIManager::gererAction( int choix, Game& game, Phase phase ) {
    switch ( choix ) {
    case 1: std::cout << "Passer a la phase suivante\n"; break;
    case 2:
        std::cout << "\n=== RECRUTEMENT ===\n";
        game.recruterHeros();
        break;
    case 3: std::cout << "Voir missions !\n";
        game.gererMissions();
        break;
    case 4:
        std::cout << "\n=== STATS / RESSOURCES ===\n";
        game.afficherStats();
        std::cout << "\nAppuyez sur Entree...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        break;
    case 5:
        std::cout << "\n=== MES HEROS ===\n";
        game.afficherMesHeros();
        std::cout << "\nAppuyez sur Entree...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        break;
    }
}

void UIManager::afficherPhase( Phase p, int jour ) const {
    std::cout << "JOUR " << jour << " - ";
    switch ( p ) {
    case Phase::Matin:   std::cout << "  MATIN"; break;
    case Phase::Journee: std::cout << " JOURNEE"; break;
    case Phase::Soir:    std::cout << " SOIR"; break;
    }
}

void UIManager::afficherActions( Phase p ) const {
    std::cout << "\n=== ACTIONS DISPONIBLES ===\n";
    std::cout << "0. Quitter le jeu\n";
    std::cout << "1. Passer a la phase suivante\n";
    std::cout << "2. Recruter heros\n";
    std::cout << "3. Voir missions\n";
    std::cout << "4. Stats / Ressources\n";
    std::cout << "5. Voir mes heros\n";
}