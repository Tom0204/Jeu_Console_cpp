#ifndef HEROES_REPOSITORY_H
#define HEROES_REPOSITORY_H

#include <vector>
#include <string>
#include "Hero.h"

class HeroesRepository {
    public:
        bool loadFromFile( const std::string& filename );
        const std::vector<Hero>& getAllHeroes() const {
            return heroes_;
        }
        std::vector<Hero> genererDrop( int nombreHeros ) const;


    private:
        std::vector<Hero> heroes_;

        Race   parseRace( const std::string& s );
        Classe parseClasse( const std::string& s );
        Rang   parseRang( const std::string& s );
};
#endif