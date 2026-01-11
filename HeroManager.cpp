#include "HeroManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

HeroManager::HeroManager() : heroesRepo() {
    srand( static_cast<unsigned>( time( nullptr )));
}

void HeroManager::chargerHeros( const std::string& filename ) {
    if ( !heroesRepo.loadFromFile( filename ))
        std::cout << "Fichier heroes.json introuvable\n";
}

std::vector<Hero> HeroManager::genererHerosPhaseMatin() {
    auto tousHeros = heroesRepo.getAllHeroes();
    if ( tousHeros.empty()) return {};

    std::vector<Hero> selection;

    std::vector<bool> utilise( tousHeros.size(), false);
    int aPrendre = std::min( 5, static_cast<int>( tousHeros.size()));

    for ( int i = 0; i < aPrendre; ++i ) {
        int idx;
        do { idx = rand() % tousHeros.size(); } while ( utilise[idx]);
        selection.push_back( tousHeros[idx]);
        utilise[idx] = true;
    }
    return selection;
}

void HeroManager::afficherHerosDisponibles( const Mission& mission ) const {
    std::cout << "\nVos heros (" << mission.nbHerosMin << "-" << mission.nbHerosMax << "):\n";
    for ( size_t i = 0; i < herosJoueur.size(); ++i ) {
        const auto& h = herosJoueur[i];
        bool ok = h.getFatigue() < 80;
        std::cout << ( i + 1 ) << ". " << h.getName() << " (fatigue:" << h.getFatigue()
            << "%) [" << (ok ? "OK" : "NO") << "]\n";
    }
}

bool HeroManager::heroEstDispoPourMission( int indexHero, Phase phaseActuelle ) const {
    if ( indexHero < 0 || indexHero >= static_cast<int>( herosJoueur.size())) return false;

    const Hero& hero = herosJoueur[indexHero];

    if ( hero.getFatigue() >= 70 ) return false;

    if ( hero.getFatigue() == 100 ) return false;

    return true;
}

void HeroManager::gererFatigueHerosRepos( std::vector<MissionEnCours>& missions ) {
    for ( auto& hero : herosJoueur ) {
        bool enMission = false;
        for ( const auto& mission : missions ) {
            for ( int idx : mission.indicesHeros ) {
                if ( memeHeroMemeRang( hero, herosJoueur[idx])) {
                    enMission = true;
                    break;
                }
            }
            if ( enMission ) break;
        }
        if ( !enMission ) {
            hero.setFatigue( hero.getFatigue() - 20 );
        }
    }
}

bool HeroManager::dejaRecrute( const Hero& h ) const
{
    for ( const auto& possede : herosJoueur ) {
        if ( memeHeroMemeRang( possede, h )) {
            return true;
        }
    }
    return false;
}