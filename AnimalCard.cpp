// fait par Jonathan Guillotte-Blouin

#include "AnimalCard.h"

AnimalCard::AnimalCard(char carteContenu[]) {
	for (int i = 0; i < 4; ++i)
		carte[i] = carteContenu[i];
}

AnimalCard::AnimalCard(char carteContenu) {
	if (carteContenu == 'j' || carteContenu == 'c')
		wildCard = true;
	else if (carteContenu == 'B' || carteContenu == 'D' || carteContenu == 'H' || carteContenu == 'M' || carteContenu == 'W')
		actionCard = true;

	for (int i = 0; i < 4; ++i)
		carte[i] = carteContenu;
}

void AnimalCard::setOrientation(Orientation newOrientation) {
	if (orientation != newOrientation) {
		orientation = newOrientation;

		// swap top-left with bottom-right
		char tmp = carte[0];
		carte[0] = carte[3];
		carte[3] = tmp;

		// swap top-right with bottom-left
		tmp = carte[1];
		carte[1] = carte[2];
		carte[2] = tmp;
	}
	
}

void AnimalCard::setRow(EvenOdd row) const {
	row == EvenOdd::ODD ? 
		printIndex = 0 : 
		printIndex = 2 ;
}

void AnimalCard::printRow(EvenOdd row) const {
	setRow(row);

	for (int i = printIndex; i < printIndex + 2; ++i)
		cout << carte[i];
}

char AnimalCard::get(string rowS, string colS) const {
	int row = (rowS == "TOP") ? 
		row = 0 : 
		row = 1;

	int col = (colS == "LEFT") ? 
		col = 0 : 
		col = 1;

	return carte[(2 * row) + col];
}

bool AnimalCard::isWildCard() const { return wildCard; }

bool AnimalCard::isActionCard() const { return actionCard; }