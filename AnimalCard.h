#ifndef ANIMAL_CARD_H
#define ANIMAL_CARD_H

// fait par Jonathan Guillotte-Blouin

#include <iostream>
#include <string>
#include "IllegalPlacement.h"

using namespace std;


enum class Orientation { UP, DOWN };
enum class EvenOdd {ODD, EVEN };


class AnimalCard {
private:
	mutable bool wildCard = false; // si Joker ou StartCard
	mutable bool actionCard = false; // si une ActionCard
	mutable int printIndex = 0; // ou commencer le print (0 ou 2)
	virtual void setRow(EvenOdd) const;

protected:
	Orientation orientation = Orientation::UP;
	char carte[4];

public:
	AnimalCard() = default;
	AnimalCard(char);
	AnimalCard(char[]);

	virtual void setOrientation(Orientation);
	virtual void printRow(EvenOdd) const;
	virtual char get(string, string) const;
	virtual bool isWildCard() const;
	virtual bool isActionCard() const;
};

#endif