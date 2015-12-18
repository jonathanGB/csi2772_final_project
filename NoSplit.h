#ifndef NO_SPLIT_H
#define NO_SPLIT_H

// fait par Jonathan Guillotte-Blouin

#include "AnimalCard.h"

class NoSplit : public AnimalCard {
private:
	static const int numOfAnimals = 1;

public:
	NoSplit() = default;
	NoSplit(char cardContent) : AnimalCard(cardContent) {};
};

#endif