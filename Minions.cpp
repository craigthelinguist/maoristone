
#include "Minions.h"

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
