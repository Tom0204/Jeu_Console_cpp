#include "MissionManager.h"
#include "include/nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using json = nlohmann::json;
MissionManager::MissionManager() {}

std::vector<Mission> MissionManager::chargerMissions() {
    std::vector<Mission> missions;

    std::ifstream file("Data/missions.json");
    if (!file.is_open()) {
        std::cout << "[ERREUR] missions.json introuvable\n";
        return missions;
    }

    try {
        nlohmann::json j;
        file >> j;

        std::cout << "[DEBUG] JSON valide, " << j.size() << " missions\n";

        for (size_t i = 0; i < j.size(); i++) {
            const auto& missionJson = j[i];

            // ? VÉRIFIE TOUTES les clés AVANT usage
            if (!missionJson.contains("nom") || !missionJson.contains("recompenses")) {
                std::cout << "[ERREUR] Mission " << i << " manque nom/recompenses\n";
                continue;
            }

            Mission m;
            m.nom = missionJson["nom"];
            m.description = missionJson.value("description", "Mission sans description");
            m.niveauGuildeMinimum = missionJson.value("niveauGuildeMinimum", 1);
            m.difficulte = missionJson.value("difficulte", 1);
            m.nbHerosMin = missionJson.value("nbHerosMin", 1);
            m.nbHerosMax = missionJson.value("nbHerosMax", 3);

            // Moment sécurisé
            std::string moment = missionJson.value("moment", "Matin");
            m.momentDisponible = (moment.find("Matin") != std::string::npos) ?
                MomentMission::Matin : MomentMission::Soir;

            // ? RÉCOMPENSES avec .value() sécurisé
            auto recomp = missionJson["recompenses"];
            m.recompenses.or_ = recomp.value("or", 0);
            m.recompenses.nourriture = recomp.value("nourriture", 0);
            m.recompenses.reputation = recomp.value("reputation", 0);
            m.recompenses.bois = recomp.value("bois", 0);
            m.recompenses.pierre = recomp.value("pierre", 0);
            m.recompenses.metal = recomp.value("metal", 0);

            std::cout << "[DEBUG] '" << m.nom << "' or=" << m.recompenses.or_
                << " nour=" << m.recompenses.nourriture << "\n";
            missions.push_back(m);
        }
    }
    catch (const std::exception& e) {
        std::cout << "[ERREUR JSON] " << e.what() << "\n";
    }

    std::cout << "[DEBUG] " << missions.size() << " missions chargées\n";
    return missions;
}

std::vector<Mission> MissionManager::getMissionsDisponiblesPourPhase( Phase phase, int niveauGuilde ) const {
    std::cout << "[DEBUG] Recherche missions pour phase=" << ( int )phase << " niveau=" << niveauGuilde << "\n";
    std::vector<Mission> dispo;
    for ( const auto& m : toutesLesMissions ) {
        if ( niveauGuilde < m.niveauGuildeMinimum ) continue;
        if ( phase == Phase::Matin && m.momentDisponible == MomentMission::Matin ) dispo.push_back(m);
        if ( phase == Phase::Journee ) dispo.push_back( m );
        if ( phase == Phase::Soir && m.momentDisponible == MomentMission::Soir ) dispo.push_back(m);
    }
    return dispo;
}

bool MissionManager::lancerMission( const Mission& missionChoisie, const std::vector<int>& indicesHeros, Phase currentPhase, int jourActuel,
    std::vector<MissionEnCours>& missionsEnCours )
{
    MissionEnCours mec;
    mec.mission = missionChoisie;
    mec.indicesHeros = indicesHeros;
    mec.phaseRetour = currentPhase;
    mec.jourRetour = jourActuel + 1;

    missionsEnCours.push_back( mec );
    return true;
}

void MissionManager::mettreAJourMissionsEnCours( Phase phase, int jour, Ressources& ressources ) {
    std::cout << "[DEBUG] Vérif récompenses phase " << ( phase == Phase::Matin ? "Matin" : "Autre" ) << "\n";
}

void MissionManager::setToutesLesMissions( const std::vector<Mission>& missions ) {
    toutesLesMissions = missions;
    std::cout << "[DEBUG] MissionManager a reçu " << toutesLesMissions.size() << " missions\n";
}