#pragma once
#ifndef HERO_MANAGER_H
#define HERO_MANAGER_H

#include "Hero.h"
#include "HeroRepository.h"
#include "Types.h"
#include <vector>

class HeroManager {
    public:
        HeroManager();
        void chargerHeros( const std::string& filename );
        std::vector<Hero> genererHerosPhaseMatin();
        void afficherHerosDisponibles( const Mission& mission ) const;
        bool heroEstDispoPourMission( int indexHero, Phase phaseActuelle ) const;
        void gererFatigueHerosRepos( std::vector<MissionEnCours>& missions );
        bool dejaRecrute( const Hero& h ) const;

        std::vector<Hero>& getHerosJoueur() { return herosJoueur; }
        const std::vector<Hero>& getHerosJoueur() const { return herosJoueur; }

    private:
        HeroesRepository heroesRepo;
        std::vector<Hero> herosJoueur;
};
#endif