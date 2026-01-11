#include "Hero.h"

Hero::Hero( const std::string& name, Race race, Classe classe, Rang rang, const Stats& stats )
    : name_( name ), race_( race ), classe_( classe ), rang_( rang ), stats_( stats ) {
    fatigue_ = 0;
}

std::string raceToString( Race r ) {
    switch ( r ) {
    case Race::Nain:   return "Nain";
    case Race::Humain: return "Humain";
    case Race::Elfe:   return "Elfe";
    }
    return "Inconnu";
}

std::string classeToString( Classe c ) {
    switch ( c ) {
    case Classe::Guerrier: return "Guerrier";
    case Classe::Mage: return "Mage";
    case Classe::Druide: return "Druide";
    case Classe::Sorcier: return "Sorcier";
    case Classe::Chevalier: return "Chevalier";
    case Classe::Eclaireur: return "Eclaireur";
    case Classe::Voleur: return "Voleur";
    case Classe::Pretre: return "Pretre";
    case Classe::Sentinelle: return "Sentinelle";
    case Classe::Champion: return "Champion";
    default: return "Inconnu";
    }
}

std::string rangToString( Rang r ) {
    switch ( r ) {
    case Rang::Commun: return "Commun";
    case Rang::Rare: return "Rare";
    case Rang::Epic: return "Epic";
    case Rang::Legendaire: return "Legendaire";
    case Rang::Mythique: return "Mythique";
    default: return "?";
    }
}

bool memeHeroMemeRang( const Hero& a, const Hero& b ) {
    return a.getName() == b.getName() && a.getRang() == b.getRang();
}

int Hero::getCoutAchat() const {
    switch ( rang_ ) {
    case Rang::Commun:     return 50;
    case Rang::Rare:       return 150;
    case Rang::Epic:       return 400;
    case Rang::Legendaire: return 1000;
    case Rang::Mythique:   return 2500;
    }
    return 50;
}

int Hero::getSalaireJournalier() const {
    switch ( rang_ ) {
    case Rang::Commun:     return 10;
    case Rang::Rare:       return 25;
    case Rang::Epic:       return 60;
    case Rang::Legendaire: return 150;
    case Rang::Mythique:   return 400;
    }
    return 10;
}