#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager() {
    initialiserRessources();
}

void ResourceManager::initialiserRessources() {
    ressources = {};
    ressources.or_ = 1000;
    ressources.nourriture = 100;
    ressources.pierre = 100;
}

void ResourceManager::afficherRessources( const Guilde& g ) const {
    std::cout << "\n RESSOURCES:\n";
    std::cout << "Or: " << ressources.or_ << " | Nourriture: " << ressources.nourriture << "\n";
    std::cout << "Reputation: " << ressources.reputation << " | Bois: " << ressources.bois << "\n";
    std::cout << "Pierre: " << ressources.pierre << " | Metal: " << ressources.metal << "\n";
}

void ResourceManager::payerNourritureHeros( int nbHeros ) {
    int cout = nbHeros * 10;
    if ( ressources.nourriture >= cout ) {
        ressources.nourriture -= cout;
        std::cout << " Nourriture payee (" << cout << ")\n";
    }
    else {
        std::cout << " Nourriture insuffisante!\n";
    }
}