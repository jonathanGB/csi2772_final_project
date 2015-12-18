#ifndef SPLIT_THREE_H
#define SPLIT_THREE_H

// fait par Jonathan Guillotte-Blouin

#include "AnimalCard.h"

class SplitThree : public AnimalCard {
public:
	SplitThree() = default;
	SplitThree(char cardContent[]) : AnimalCard(cardContent) {};
};

#endif