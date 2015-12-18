// fait par Jonathan Guillotte-Blouin

#include "Player.h"

string Player::swapSecretAnimal(string& newAnimal) { 
	string tmp = animal;

	animal = newAnimal;

	return tmp;
}

string Player::getSecretAnimal() const { return animal; }

void Player::swapHand(Player* otherPlayer) {
	Hand currHand = ownHand;
	ownHand = otherPlayer->ownHand;
	otherPlayer->ownHand = currHand;
}

void Player::printHand() const {
	cout << "Joueur: " << name << endl;
	cout << "Animal secret: " << animal << endl;
	cout << "Main:\n" << endl;
	ownHand.printHand();
}

string Player::getName() const {
	return name;
}

void Player::addCard(shared_ptr<AnimalCard> newCard) { ownHand += newCard; }

int Player::sizeOfHand() const { return ownHand.noCards(); }

shared_ptr<AnimalCard> Player::pickCard(int index) {
	shared_ptr<AnimalCard> pickedCard = ownHand[index];

	ownHand -= pickedCard;

	return pickedCard;
}