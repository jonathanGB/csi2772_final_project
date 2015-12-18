// fait par Jonathan Guillotte-Blouin

#include "Hand.h"

Hand& Hand::operator+=(shared_ptr<AnimalCard> card) {
	hand.push_back(card);
	return *this;
}

Hand& Hand::operator-=(shared_ptr<AnimalCard> card) {
	int originalSize = hand.size();

	hand.remove(card);

	if (originalSize == hand.size())
		throw MissingCard("La carte a enlevee n'existe pas dans la main");

	return *this;
}

shared_ptr<AnimalCard> Hand::operator[](int index) const {
	if (index < 0 || index >= hand.size())
		throw IllegalPlacement("Index a l'exterieur des limites");

	auto it = hand.begin();

	advance(it, index);

	return *it;
}

int Hand::noCards() const { return hand.size(); }

void Hand::printHand() const {
	for (int i = 0; i < hand.size(); ++i) {
		if (i < 10)
			cout << i << "  ";
		else
			cout << i << ' ';
	}

	cout << endl;

	for (auto it = hand.begin(); it != hand.end(); ++it) {
		it->get()->printRow(EvenOdd::ODD);
		cout << ' ';
	}

	cout << endl;

	for (auto it = hand.begin(); it != hand.end(); ++it) {
		it->get()->printRow(EvenOdd::EVEN);
		cout << ' ';
	}

	cout << endl;
}