#pragma once
#ifndef MISSION_MANAGER_H
#define MISSION_MANAGER_H

#include "Types.h"
#include <vector>

class MissionManager {
    public:
        MissionManager();
        std::vector<Mission> chargerMissions();
        std::vector<Mission> getMissionsDisponiblesPourPhase( Phase phase, int niveauGuilde ) const;
        bool lancerMission( const Mission& missionChoisie, const std::vector<int>& indicesHeros, Phase currentPhase, int jourActuel,
            std::vector<MissionEnCours>& missionsEnCours);
        void setToutesLesMissions( const std::vector<Mission>& missions );
        void mettreAJourMissionsEnCours( Phase phase, int jour, Ressources& ressources );
        std::vector<MissionEnCours>& getMissionsEnCours() { return missionsEnCours; };
        const std::vector<MissionEnCours>& getMissionsEnCours() const { return missionsEnCours; }

    private:
        std::vector<Mission> toutesLesMissions;
        std::vector<MissionEnCours> missionsEnCours;
};
#endif