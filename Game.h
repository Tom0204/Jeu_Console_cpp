#pragma once
#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include "MissionManager.h"
#include "HeroManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "Guilde.h"

class Game {
    public:
        Game();
        void run();
        void passerPhase();
        void recruterHeros();
        void afficherStats();
        MissionManager& getMissionManager() { return missionManager; }
        void afficherMesHeros();
        void gererMissions();

    private:
        MissionManager missionManager;
        HeroManager heroManager;
        ResourceManager resourceManager;
        UIManager uiManager;
        Guilde guilde;
        Phase currentPhase = Phase::Matin;
        int jourActuel = 0;
        bool isRunning = true;
        int dernierJourNourriture = 0;
        std::vector<MissionEnCours> missionsActuelles;
        std::vector<Mission> toutesLesMissions;
};
#endif