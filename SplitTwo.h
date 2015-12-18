#ifndef SPLIT_TWO_H
#define SPLIT_TWO_H

// fait par Jonathan Guillotte-Blouin

#include "AnimalCard.h"

class SplitTwo : public AnimalCard {
public:
	SplitTwo() = default;
	SplitTwo(char cardContent[]) : AnimalCard(cardContent) {};
};

#endif