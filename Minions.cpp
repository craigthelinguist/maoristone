
#include "Minions.h"

bool operator== (Minion m1, Minion m2)
{
    return &m1 == &m2;
}

bool Minion::isDead ()
{
    return this->currentHealth < this->stats->maxHealth;
}

void Minion::damage (int amount)
{
    this->currentHealth -= amount;
}

int main(int argc, char **argv)
{
    return 0;
}
