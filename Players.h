
#ifndef PLAYERS_H
#define PLAYERS_H

#include <algorithm>
#include <queue>

#include "Minions.h"

class Player {
 
public:
    
    /*
     * The maximum number of cards a player can hold in their hand at once. 
     */
    static const int maxHandSize = 10;
    
    /*
     * Inflict a specified amount of damage to the player. Damage is first absorbed by armour.
     */
    void damage (int amount);
    
    /*
     * Make the player draw a card. If they have no cards to draw they take fatigue damage.
     */
    void drawCard ();
    
    /*
     * True if the player is holding the maximum amount of cards.
     */
    bool handIsFull ();
    
    /*
     * True if the player has no health left.
     */
    bool isDead ();
    
    /*
     * True if the player has no cards left in their deck.
     */
    bool outOfCards ();
    
private:
    int amountOverdrawn;
    //SDL_Surface *avatarImage;
    int currentArmour;
    int currentHealth;
    std::queue<Minion> deck;
    std::vector<Minion> hand;
    
};


#endif
