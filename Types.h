#pragma once
#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>

enum class Phase { Matin, Journee, Soir };
enum class MomentMission { Matin, Soir, MatinEtSoir };

struct MissionRecompenses {
    int or_ = 0;
    int reputation = 0;
    int nourriture = 0;
    int bois = 0;
    int pierre = 0;
    int metal = 0;
};

struct Mission {
    int id = 0;
    std::string nom;
    std::string description;
    int niveauGuildeMinimum = 0;
    int difficulte = 1;
    int nbHerosMin = 1;
    int nbHerosMax = 3;
    int dureeJours = 2;
    MomentMission momentDisponible;
    MissionRecompenses recompenses;
};

struct MissionEnCours {
    Mission mission;
    std::vector<int> indicesHeros;
    Phase phaseRetour;
    int jourRetour;
};

struct Ressources {
    int or_ = 1000;
    int reputation = 0;
    int nourriture = 0;
    int objetsSoin = 0;
    int bois = 0;
    int pierre = 0;
    int metal = 0;
};
#endif