
#ifndef MINIONS_H
#define MINIONS_H

#include "CardStats.h"

class Minion {
 
public:
    
    /*
     * This is reference equality, not value equailty.
     */
    friend bool operator== (Minion m1, Minion m2);
    
    /*
     * True if the minion has no health left.
     */
    bool isDead ();
    
    /*
     * Damage the minion by a specified amount.
     */
    void damage (int amount);
    
private:
    struct CardStats *stats;
    SDL_Surface *image;
    int currentHealth;
    
};

#endif

