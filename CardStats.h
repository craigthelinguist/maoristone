

#ifndef CARDSTATS_H
#define CARDSTATS_H

#include <string>

#include "Modules.h"
#include LIBRARY(SDL.h)

/*
 * A struct encapsulating the various stats of a card, such as its name, max health, mana cost, etc.
 */
struct CardStats {
    int maxHealth;
    int manaCost;
    std::string name;
};

/*
 * Make and return a struct card.
 */
struct CardStats makeCardStats (int, int, std::string);

#endif
