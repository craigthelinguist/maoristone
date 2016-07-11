
#include "CardStats.h"

struct CardStats makeCardStats (int maxHealth, int manaCost, std::string name)
{
    struct CardStats card_stats;
    card_stats.maxHealth = maxHealth;
    card_stats.manaCost = manaCost;
    card_stats.name = name;
    return card_stats;
}


