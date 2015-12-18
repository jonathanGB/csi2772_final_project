#ifndef ANIMAL_CARD_FACTORY_H
#define ANIMAL_CARD_FACTORY_H

// fait par Jonathan Guillotte-Blouin

#include <random>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <memory>
#include "Deck.h"
#include "Joker.h"
#include "BearAction.h"
#include "DeerAction.h"
#include "HareAction.h"
#include "MooseAction.h"
#include "WolfAction.h"
#include "SplitTwo.h"
#include "SplitThree.h"
#include "SplitFour.h"

class AnimalCardFactory {
private:
	Deck<shared_ptr<AnimalCard>> deck;
	AnimalCardFactory();

	void generateCards();
	char getAnimal(int) const;
	int getSecondIndex(int) const;

public:
	static AnimalCardFactory* getFactory();
	Deck<shared_ptr<AnimalCard>> getDeck();
};

#endif