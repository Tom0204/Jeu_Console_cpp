#include "HeroRepository.h"
#include "include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using json = nlohmann::json;

Race HeroesRepository::parseRace( const std::string& s ) {
    if ( s == "Nain" )   return Race::Nain;
    if ( s == "Humain" ) return Race::Humain;
    if ( s == "Elfe" )   return Race::Elfe;
    return Race::Humain;
}

Classe HeroesRepository::parseClasse( const std::string& s ) {
    if ( s == "Guerrier" ) return Classe::Guerrier;
    if ( s == "Mage" ) return Classe::Mage;
    if ( s == "Druide" ) return Classe::Druide;
    if ( s == "Sorcier" ) return Classe::Sorcier;
    if ( s == "Chevalier" ) return Classe::Chevalier;
    if ( s == "Eclaireur" ) return Classe::Eclaireur;
    if ( s == "Voleur" ) return Classe::Voleur;
    if ( s == "Pretre" ) return Classe::Pretre;
    if ( s == "Sentinelle" ) return Classe::Sentinelle;
    if ( s == "Champion" ) return Classe::Champion;
    return Classe::Guerrier;
}

Rang HeroesRepository::parseRang( const std::string& s ) {
    if ( s == "commun" ) return Rang::Commun;
    if ( s == "rare" ) return Rang::Rare;
    if ( s == "epic" ) return Rang::Epic;
    if ( s == "legendaire" ) return Rang::Legendaire;
    if ( s == "mythique" ) return Rang::Mythique;
    return Rang::Commun;
}

bool HeroesRepository::loadFromFile( const std::string& filename ) {
    static bool seedInitialized = false;
    if ( !seedInitialized ) {
        srand( static_cast<unsigned>( time( nullptr )));
        seedInitialized = true;
    }

    std::ifstream file( filename );
    if ( !file ) {
        std::cerr << "Impossible d'ouvrir " << filename << "\n";
        return false;
    }

    json j;
    file >> j;
    heroes_.clear();

    for ( const auto& h : j["heroes"]) {
        std::string name = h["name"].get<std::string>();
        std::string raceS = h["race"].get<std::string>();
        std::string clsS = h["class"].get<std::string>();
        std::string rangS = h["rank"].get<std::string>();

        Stats st;
        st.hp = h["stats"]["hp"].get<int>();
        st.strength = h["stats"]["strength"].get<int>();
        st.endurance = h["stats"]["endurance"].get<int>();
        st.magic = h["stats"]["magic"].get<int>();
        st.agility = h["stats"]["agility"].get<int>();

        heroes_.emplace_back(
            name,
            parseRace( raceS ),
            parseClasse( clsS ),
            parseRang( rangS ),
            st
        );
    }
    return true;
}

std::vector<Hero> HeroesRepository::genererDrop( int nombreHeros ) const {
    std::vector<Hero> drop;
    std::vector<int> poids = { 70, 20, 8, 1, 1 };  // %drop des héros : Commun=70%, Rare=20%, etc.

    for ( int i = 0; i < nombreHeros; ++i )     {
        int randPoids = rand() % 100;
        int cumul = 0;

        for ( int r = 0; r < 5; ++r ) {
            cumul += poids[r];
            if ( randPoids < cumul ) {
                for ( const auto& hero : heroes_ ) {
                    if ( static_cast<int>( hero.getRang()) == r && drop.size() < static_cast<size_t>( nombreHeros )) {
                        drop.push_back( hero );
                        break;
                    }
                }
                break;
            }
        }
    }
    return drop;
}