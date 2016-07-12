
#include "Players.h"

bool Player::handIsFull ()
{
    return this->hand.size() == Player::maxHandSize;
}
    
bool Player::outOfCards ()
{
    return this->deck.size() == 0;
}
    
void Player::drawCard ()
{
    // If player is out of cards, deal damage proportional to how many times they've overdrawn.
    if (this->outOfCards()) {
	this->amountOverdrawn++;
	this->currentHealth -= this->amountOverdrawn;
    }
    
    // Otherwise draw a card from deck and place it in their hand.
    else {
	Minion m = this->deck.front();
	this->deck.pop();
	if (!this->handIsFull()) {
	    this->hand.push_back(m);
	}
    }
}

void Player::damage (int amount)
{
    // Figure out how much damage is done to armour (0 if no armour, or some positive value if there is some armour).
    int damage2armour = std::max(0, this->currentArmour - amount);
    this->currentArmour -= damage2armour;
    
    // Any left over damages the health (0 if armour absorbed all of the damage).
    amount -= damage2armour;
    this->currentHealth -= amount;
}

bool Player::isDead ()
{
    return this->currentHealth <= 0;
}

int main (int argc, char ** argv){
    return 0;
    
}