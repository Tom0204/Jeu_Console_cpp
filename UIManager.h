#pragma once
#include "Types.h"
#include "Guilde.h"
#include "Hero.h"
#include <iostream>

class Game;

class UIManager {
public:
    int gererChoix( const Game& game, Phase phase );
    void gererAction( int choix, Game& game, Phase phase );
    void afficherPhase( Phase p, int jour ) const;
    void afficherActions( Phase p ) const;
};