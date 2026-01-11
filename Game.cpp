#include "Game.h"
#include <iostream>
#include <limits>
#include <string>

Game::Game() : currentPhase( Phase::Matin ), isRunning( true ), missionManager(), heroManager(), resourceManager(), uiManager(), 
    guilde( "Guilde par defaut" ) {
    toutesLesMissions = missionManager.chargerMissions();
    missionManager.setToutesLesMissions( toutesLesMissions );

    heroManager.chargerHeros( "Data/heroes.json" );
    resourceManager.initialiserRessources();
}
    

int lireChoixUnique( int min, int max )
{
    while ( true ) {
        std::string input;
        std::getline( std::cin >> std::ws, input );

        if ( input.empty()) {
            std::cout << "Entree vide, entre un nombre entre "
                << min << " et " << max << ".\n";
            continue;
        }

        bool ok = true;
        for ( char c : input ) {
            if ( !std::isdigit( static_cast<unsigned char>( c ))) {
                ok = false;
                break;
            }
        }
        if ( !ok ) {
            std::cout << "Entree invalide, entre un seul nombre entre "
                << min << " et " << max << ".\n";
            continue;
        }

        int valeur = std::stoi( input );
        if ( valeur < min || valeur > max ) {
            std::cout << "Choix hors limites (" << min << "-" << max << ").\n";
            continue;
        }
        return valeur;
    }
}

void Game::run() {
    while ( isRunning ) {

        if ( currentPhase == Phase::Matin && jourActuel != dernierJourNourriture ) {
            int nbHeros = heroManager.getHerosJoueur().size();
            resourceManager.payerNourritureHeros( nbHeros );
            int totalSalaire = 0;

            for ( const auto& hero : heroManager.getHerosJoueur()) {
                totalSalaire += hero.getSalaireJournalier();
            }

            Ressources& res = resourceManager.getRessources();

            if ( res.or_ >= totalSalaire ) {
                res.or_ -= totalSalaire;
                std::cout << "Salaires payes (" << totalSalaire << " or)\n";
            }
            else {
                std::cout << "Salaires insuffisants !\n";
            }
            dernierJourNourriture = jourActuel;
        }

        uiManager.afficherPhase(currentPhase, jourActuel);
        resourceManager.afficherRessources(guilde);

        while ( true ) {
            int choix = uiManager.gererChoix( *this, currentPhase );

            if ( choix == 0 ) { isRunning = false; break; }
            if ( choix == 1 ) break;

            uiManager.gererAction(choix, *this, currentPhase);
        }

        if (!isRunning) break;
        passerPhase();
    }
}

void Game::passerPhase() {
    if (currentPhase == Phase::Soir) {
        jourActuel++;
    }

    for ( auto it = missionsActuelles.begin(); it != missionsActuelles.end(); ) {
        if ( it->phaseRetour == currentPhase ) {


            std::cout << "[DEBUG] Récolte de bois: or=" << it->mission.recompenses.or_
                << " nour=" << it->mission.recompenses.nourriture
                << " bois=" << it->mission.recompenses.bois
                << " reput=" << it->mission.recompenses.reputation << "\n";



            std::cout << "Mission TERMINEE ! +"
                << it->mission.recompenses.or_ << "or +"
                << it->mission.recompenses.nourriture << "nourriture\n";

            Ressources& res = resourceManager.getRessources();
            res.or_ += it->mission.recompenses.or_;
            res.nourriture += it->mission.recompenses.nourriture;
            res.reputation += it->mission.recompenses.reputation;
            res.bois += it->mission.recompenses.bois;
            res.pierre += it->mission.recompenses.pierre;
            res.metal += it->mission.recompenses.metal;

            it = missionsActuelles.erase( it );
        }
        else {
            ++it;
        }
    }
}


void Game::recruterHeros()
{
    while ( true ) {
        auto candidats = heroManager.genererHerosPhaseMatin();
        std::vector<Hero> disponibles;

        for ( const auto& h : candidats ) {
            if ( !heroManager.dejaRecrute( h )) {
                disponibles.push_back( h );
            }
        }

        if ( disponibles.empty()) {
            std::cout << "Aucun heros recrutable (tu les as deja tous).\n";
            return;
        }

        std::cout << "\nHEROS DISPONIBLES AU RECRUTEMENT :\n";
        for ( size_t i = 0; i < disponibles.size(); ++i ) {
            const auto& hero = disponibles[i];
            std::cout << ( i + 1 ) << ". " << hero.getName()
                << " (" << rangToString(hero.getRang()) << ") "
                << "Argent " << hero.getCoutAchat()
                << " | Salaire/jour : " << hero.getSalaireJournalier()
                << "\n";
        }
        std::cout << "0. Terminer le recrutement\nChoix : ";
        int choix = lireChoixUnique( 0, static_cast<int>( disponibles.size()));

        if ( choix == 0 ) {
            std::cout << "Fin du recrutement.\n";
            break;
        }

        Hero choisi = disponibles[choix - 1];

        if ( heroManager.dejaRecrute( choisi )) {
            std::cout << "Tu as déjà ce héros.\n";
            continue;
        }

        Ressources& res = resourceManager.getRessources();
        int cout = choisi.getCoutAchat();

        if ( res.or_ < cout ) {
            std::cout << "Or insuffisant (" << cout << " requis).\n";
            continue;
        }

        res.or_ -= cout;
        heroManager.getHerosJoueur().push_back(choisi);
        std::cout << "OK " << choisi.getName() << " recrute !\n";
    }
}

void Game::afficherStats()
{
    std::cout << "\n===== STATS / RESSOURCES =====\n";
    resourceManager.afficherRessources(guilde);
    std::cout << "Nombre de heros : " << heroManager.getHerosJoueur().size() << "\n";
}

void Game::afficherMesHeros() {
    const auto& mesHeros = heroManager.getHerosJoueur();
    std::cout << "\n === MES HEROS (" << mesHeros.size() << ") ===\n";

    if ( mesHeros.empty()) {
        std::cout << "Aucun heros recrute.\n";
        return;
    }

    for ( size_t i = 0; i < mesHeros.size(); ++i ) {
        const auto& hero = mesHeros[i];
        std::cout << ( i + 1 ) << ". " << hero.getName()
            << " | " << raceToString( hero.getRace())
            << " " << classeToString( hero.getClasse())
            << " [" << rangToString( hero.getRang()) << "]"
            << "\nStats: HP:" << hero.getStats().hp
            << " STR:" << hero.getStats().strength
            << " END:" << hero.getStats().endurance
            << " MAG:" << hero.getStats().magic
            << " AGI:" << hero.getStats().agility
            << " | Fatigue: " << hero.getFatigue() << "%"
            << " | Salaire: " << hero.getSalaireJournalier() << "/j\n";
    }
    std::cout << "\nCoût nourriture/jour: " << ( mesHeros.size() * 10 ) << "\n";
}

void Game::gererMissions() {
    auto missionsDispo = missionManager.getMissionsDisponiblesPourPhase( currentPhase, guilde.getNiveau());

    if ( missionsDispo.empty()) {
        std::cout << "Aucune mission cette phase.\n";
        return;
    }

    std::cout << "\nMISSIONS (" << ( currentPhase == Phase::Matin ? "MATIN" : currentPhase == Phase::Journee ? "JOURNEE" : "SOIR" ) << ")\n";

    for ( size_t i = 0; i < missionsDispo.size(); ++i ) {
        const auto& m = missionsDispo[i];
        std::cout << (i + 1) << ". " << m.nom << " (Diff:" << m.difficulte
            << " | Heros:" << m.nbHerosMin << "-" << m.nbHerosMax << ")\n";
    }

    std::cout << "0. Retour\nChoix ? ";
    int choixMission;
    std::cin >> choixMission;
    if ( choixMission < 1 || choixMission > static_cast<int>( missionsDispo.size())) return;

    Mission missionChoisie = missionsDispo[choixMission - 1];

    std::cout << "\nChoisir " << missionChoisie.nbHerosMin << "-"
        << missionChoisie.nbHerosMax << " heros :\n";
    heroManager.afficherHerosDisponibles( missionChoisie );

    std::vector<int> indicesHeros;
    std::cout << "Indices heros (un par un, 0=fin) : ";

    while ( indicesHeros.size() < missionChoisie.nbHerosMax ) {
        int idxHero;
        std::cin >> idxHero;
        if ( idxHero == 0 ) break;

        idxHero--;
        if ( idxHero < 0 || idxHero >= static_cast<int>( heroManager.getHerosJoueur().size())) {
            std::cout << "Index invalide\n";
            continue;
        }

        if ( !heroManager.heroEstDispoPourMission( idxHero, currentPhase )) {
            std::cout << "Heros fatigue/indisponible\n";
            continue;
        }

        bool dejaDansMission = false;
        for ( int idx : indicesHeros ) {
            if ( idx == idxHero ) {
                dejaDansMission = true;
                break;
            }
        }
        if ( dejaDansMission ) {
            std::cout << "Heros deja selectionne\n";
            continue;
        }

        indicesHeros.push_back( idxHero );
        std::cout << "Heros " << ( idxHero + 1 ) << " ajoute ("
            << indicesHeros.size() << "/" << missionChoisie.nbHerosMin << ")\n";

        if ( indicesHeros.size() >= missionChoisie.nbHerosMin ) {
            std::cout << "0=fin, ou continue (max " << missionChoisie.nbHerosMax << ") : ";
        }
    }

    if ( indicesHeros.size() >= static_cast<size_t>( missionChoisie.nbHerosMin )) {
        for (int idx : indicesHeros) {
            heroManager.getHerosJoueur()[idx].setFatigue( 30 );
        }

        if ( missionManager.lancerMission( missionChoisie, indicesHeros, currentPhase, jourActuel, missionsActuelles )) {
            std::cout << "Mission '" << missionChoisie.nom << "' lancee ! Missions en cours : "
                << missionsActuelles.size() << "\n";
        }
        else {
            std::cout << "ECHEC lancer mission !\n";
        }
    }
    else {
        std::cout << "Pas assez de heros (" << indicesHeros.size()
            << "/" << missionChoisie.nbHerosMin << " requis)\n";
    }
}