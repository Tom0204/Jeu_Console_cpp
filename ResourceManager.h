#pragma once
#include "Types.h"
#include "Guilde.h"

class ResourceManager {
public:
    ResourceManager();
    void initialiserRessources();
    Ressources& getRessources() { return ressources; }
    void afficherRessources( const Guilde& g ) const;
    void payerNourritureHeros( int nbHeros );
private:
    Ressources ressources;
};