
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

bool Player::playMinion (Minion minion2play, int position)
{
    
    // If there's no space on the field you can't play the minion.
    if (this->field.count(position) != 0) return false;
    
    // Check if you have the minion in your hand.
    int indexOfMinion = -1;
    for (std::vector<Minion>::size_type i= 0; i != this->hand.size(); i++) {
	if (this->hand[i] == minion2play) {
	    indexOfMinion = i;
	    break;
	}
    }
    
    // If you don't have the minion then you can't play it.
    if (!indexOfMinion == -1) return false;
    
    // Put the minion into play & take it out of your hand.
    this->field[position] = minion2play;
    this->hand.erase(this->hand.begin() + indexOfMinion);
    
}

int main (int argc, char ** argv){
    return 0;
    
}