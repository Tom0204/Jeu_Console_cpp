#include "Guilde.h"

Guilde::Guilde( const std::string& nom_ ) : nom( nom_ ), niveau( 1 ), reputation( 0 ) {
}

int Guilde::getCapaciteStockage() const {
    // Capacité : Niveau 1 = 100 unités pour chaque ressource et +50 par niveau
    return 100 + ( niveau - 1 ) * 50;
}

bool Guilde::peutAjouterRessource( const std::string& /*type*/, int quantite ) const {
    return quantite <= getCapaciteStockage();
}

void Guilde::setNiveau( int nouveauNiveau ) {
    if ( nouveauNiveau > niveau )
    {
        niveau = nouveauNiveau;
    }
}