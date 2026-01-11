#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>

enum class Race {
    Nain,
    Humain,
    Elfe
};

enum class Classe {
    Guerrier, Mage, Druide, Sorcier, Chevalier, Eclaireur,
    Voleur, Pretre, Sentinelle, Champion
};

enum class Rang {
    Commun, Rare, Epic, Legendaire, Mythique
};

struct Stats {
    int hp;
    int strength;
    int endurance;
    int magic;
    int agility;
};

class Hero {
    public:
        Hero( const std::string& name, Race race, Classe classe, Rang rang, const Stats& stats );
        const std::string& getName() const { return name_; }
        Race  getRace()   const { return race_; }
        Classe getClasse() const { return classe_; }
        Rang  getRang()   const { return rang_; }
        const Stats& getStats() const { return stats_; }

        int getCoutAchat() const;
        int getSalaireJournalier() const;
        int getFatigue() const { return fatigue_; }
        void setFatigue( int f ) { fatigue_ = std::max( 0, std::min( 100, f )); }

    private:
        std::string name_;
        Race   race_;
        Classe classe_;
        Rang   rang_;
        Stats  stats_;
        int fatigue_ = 0;
};

std::string raceToString( Race r );
std::string classeToString( Classe c );
std::string rangToString( Rang r );

bool memeHeroMemeRang( const Hero& a, const Hero& b );
#endif