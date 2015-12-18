#ifndef MISSING_CARD_H
#define MISSING_CARD_H

// fait par Jonathan Guillotte-Blouin

#include <iostream>
#include <string>

using namespace std;

class MissingCard {
public:
	MissingCard(string errorMessage) { cout << errorMessage << endl; }
};

#endif