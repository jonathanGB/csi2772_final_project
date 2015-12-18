#ifndef HAND_H
#define HAND_H

// fait par Jonathan Guillotte-Blouin

#include <memory>
#include <list>
#include "AnimalCard.h"
#include "MissingCard.h"

class Hand {
private:
	list<shared_ptr<AnimalCard>> hand;

public:
	Hand() = default;
	Hand(const Hand& otherHand) : hand(otherHand.hand) {};
	Hand& operator+=(shared_ptr<AnimalCard>);
	Hand& operator-=(std::shared_ptr<AnimalCard>);
	shared_ptr<AnimalCard> operator[](int) const;
	int noCards() const;
	void printHand() const;
};

#endif