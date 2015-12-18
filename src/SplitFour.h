#ifndef SPLIT_FOUR_H
#define SPLIT_FOUR_H

// fait par Jonathan Guillotte-Blouin

#include "AnimalCard.h"

class SplitFour : public AnimalCard {
public:
	SplitFour() = default;
	SplitFour(char cardContent[]) : AnimalCard(cardContent) {};
};

#endif