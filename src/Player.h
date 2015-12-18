#ifndef PLAYER_H
#define PLAYER_H

// fait par Jonathan Guillotte-Blouin

#include "Hand.h"

class Player {
private:
	string name;
	string animal;
	Hand ownHand;

public:
	Player() = default;
	Player(string& newName, string newAnimal) :
		name(newName), animal(newAnimal) {};
	Player(string newName, string newAnimal, const Hand& newHand) :
		name(newName), animal(newAnimal), ownHand(newHand) {};

	string swapSecretAnimal(string&);
	string getSecretAnimal() const;
	void swapHand(Player*);
	void printHand() const;
	string getName() const;
	void addCard(shared_ptr<AnimalCard>);
	int sizeOfHand() const;
	shared_ptr<AnimalCard> pickCard(int);
};

#endif