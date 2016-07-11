
#ifndef MINIONS_H
#define MINIONS_H

#include "CardStats.h"

class Minion {
 
public:
    bool isDead ();
    void damage (int amount);
    
private:
    struct CardStats *stats;
    SDL_Surface *image;
    int currentHealth;
    
};

#endif

