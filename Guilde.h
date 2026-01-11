#ifndef GUILDE_H
#define GUILDE_H

#include <string>

class Guilde {
    public:
        Guilde(const std::string& nom);

        std::string getNom() const { return nom; }
        int getNiveau() const { return niveau; }
        int getCapaciteStockage() const;

        bool peutAjouterRessource( const std::string& type, int quantite ) const;
        void setNiveau( int nouveauNiveau );

    private:
        std::string nom;
        int niveau;
        int reputation;
};
#endif