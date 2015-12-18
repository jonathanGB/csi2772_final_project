// fait par Jonathan Guillotte-Blouin

#include "Table.h"

Table::Table() {
	table[52][52].reset(new StartCard());

	numOfAnimals = vector<int>(5, 0);
}

int Table::getAnimalMatch(int row, int col, AnimalCard* baseCard) const {
	if (baseCard->isWildCard()) {
		return 1;
	}

	int count = 0;
	vector<char> animalsMatched;
	char c;
	bool overWildCard = false, underWildCard = false, rightWildCard = false, leftWildCard = false; // savoir si les cartes autour sont des Joker ou des StartCard

	// carte au-desssus
	if (row - 1 >= 0) {
		AnimalCard* cardOver = table[row - 1][col].get();
		
		if (cardOver == nullptr)
			;
		else if (cardOver->isWildCard())
			overWildCard = true;
		else {
			if ((c = cardOver->get("BOTTOM", "LEFT")) == baseCard->get("TOP", "LEFT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}

			if ((c = cardOver->get("BOTTOM", "RIGHT")) == baseCard->get("TOP", "RIGHT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}
		}
	}

	// card en-dessous
	if (row + 1 < SIZE_OF_TABLE) {
		AnimalCard* cardUnder = table[row + 1][col].get();

		if (cardUnder == nullptr)
			;
		else if (cardUnder->isWildCard())
			underWildCard = true;
		else {
			if ((c = cardUnder->get("TOP", "LEFT")) == baseCard->get("BOTTOM", "LEFT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}

			if ((c = cardUnder->get("TOP", "RIGHT")) == baseCard->get("BOTTOM", "RIGHT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}
		}
	}

	// carte a la gauche
	if (col - 1 >= 0) {
		AnimalCard* cardLeft = table[row][col - 1].get();

		if (cardLeft == nullptr)
			;
		else if (cardLeft->isWildCard())
			leftWildCard = true;
		else {
			if ((c = cardLeft->get("TOP", "RIGHT")) == baseCard->get("TOP", "LEFT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}

			if ((c = cardLeft->get("BOTTOM", "RIGHT")) == baseCard->get("BOTTOM", "LEFT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}
		}
	}

	// carte a la droite
	if (col + 1 < SIZE_OF_TABLE) {
		AnimalCard* cardRight = table[row][col + 1].get();

		if (cardRight == nullptr)
			;
		else if (cardRight->isWildCard())
			rightWildCard = true;
		else {
			if ((c = cardRight->get("TOP", "LEFT")) == baseCard->get("TOP", "RIGHT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}

			if ((c = cardRight->get("BOTTOM", "LEFT")) == baseCard->get("BOTTOM", "RIGHT")) {
				if (!animalFound(animalsMatched, c)) {
					count++;
					animalsMatched.push_back(c);
				}
			}
		}
	}

	// condition si 0 lien direct mais au moins un joker ou startCard a cote
	if (count == 0 && (overWildCard || underWildCard || leftWildCard || rightWildCard))
		return 1;
	else
		return count;
}

bool Table::animalFound(vector<char>& list, char c) const {
	for (int i = 0; i < list.size(); ++i) {
		if (list[i] == c)
			return true;
	}

	return false;
}

void Table::updateNumOfAnimals(shared_ptr<AnimalCard> ptr, string action) {
	char anim1 = ptr.get()->get("TOP", "LEFT"), anim2 = ptr.get()->get("TOP", "RIGHT"), anim3 = ptr.get()->get("BOTTOM", "LEFT"), anim4 = ptr.get()->get("BOTTOM", "RIGHT");
	vector<char> animalsMatched;

	animalsMatched.push_back(anim1);

	if (!animalFound(animalsMatched, anim2))
		animalsMatched.push_back(anim2);

	if (!animalFound(animalsMatched, anim3))
		animalsMatched.push_back(anim3);

	if (!animalFound(animalsMatched, anim4))
		animalsMatched.push_back(anim4);


	if (action == "INSERT") {
		for (int i = 0; i < animalsMatched.size(); ++i)
			numOfAnimals[getAnimalIndex(animalsMatched[i])]++;
	}
	else if (action == "REMOVE") {
		for (int i = 0; i < animalsMatched.size(); ++i)
			numOfAnimals[getAnimalIndex(animalsMatched[i])]--;
	}
	else if (action == "INCREMENT") {
		auto it = begin(numOfAnimals);

		while (it != end(numOfAnimals))
			(*(it++))++;
	}
	else if (action == "DECREMENT") {
		auto it = begin(numOfAnimals);

		while (it != end(numOfAnimals))
			(*(it++))--;
	} 
	else 
		cout << "L'update du nombre d'animaux a une action invalide";
}

int Table::getAnimalIndex(string animal) {
	if (animal == "bear")
		return 0;
	else if (animal == "deer")
		return 1;
	else if (animal == "hare")
		return 2;
	else if (animal == "moose")
		return 3;
	else if (animal == "wolf")
		return 4;
	else 
		return -1;
}

int Table::getAnimalIndex(char animal) {
	if (animal == 'b')
		return 0;
	else if (animal == 'd')
		return 1;
	else if (animal == 'h')
		return 2;
	else if (animal == 'm')
		return 3;
	else if (animal == 'w')
		return 4;
	else
		return -1;
}

int Table::addAt(shared_ptr<AnimalCard> ptr, int row, int col, bool noExceptionThrown) {
	if (table[row][col].get() != nullptr)
		throw IllegalPlacement("Il y a deja une carte a cet emplacement!");
	else if (noExceptionThrown) {
		table[row][col] = ptr;
		return 0;
	}
	else {
		int numOfMatches;

		if ((numOfMatches = getAnimalMatch(row, col, ptr.get())) > 0) {
			table[row][col] = ptr;

			if (!ptr.get()->isWildCard())
				updateNumOfAnimals(ptr, "INSERT");
			else
				updateNumOfAnimals(ptr, "INCREMENT");
			
			return numOfMatches;
		}

		throw IllegalPlacement("Il n'y a pas de AnimalCard a apparier!");
	}
}

shared_ptr<AnimalCard> Table::pickAt(int row, int col) {
	shared_ptr<AnimalCard> returnedPtr = table[row][col];

	if (!returnedPtr.get()->isWildCard())
		updateNumOfAnimals(returnedPtr, "REMOVE");
	else
		updateNumOfAnimals(returnedPtr, "DECREMENT");

	table[row][col].reset();
	
	return returnedPtr;
}

shared_ptr<AnimalCard> Table::get(int row, int col) const { return table[row][col]; }

bool Table::win(string& animal) {
	int index = getAnimalIndex(animal);

	if (index >= 0)
		return numOfAnimals[index] >= NOMBRE_GAGNANT;
	else
		return false;
}

void Table::addPlayer(shared_ptr<Player> newPlayer) { allPlayers.push_back(newPlayer); }

vector<shared_ptr<Player>> Table::getPlayers() const { return allPlayers; }

void Table::printTable() const {
	cout << endl << endl << "  |";
	// imprime les numeros de colonne en haut
	for (int i = 0; i < SIZE_OF_TABLE; ++i) {
		if (i < 10)
			cout << i << " |";
		else if (i < 100)
			cout << i << '|';
		else
			cout << i;
	}

	cout << endl;

	for (int i = 0; i < SIZE_OF_TABLE; ++i) {
		for (int j = 0; j <= SIZE_OF_TABLE; ++j)
			cout << "---";

		cout << endl;

		if (i < 10)
			cout << i << " |";
		else if (i < 100)
			cout << i << '|';
		else
			cout << i;

		for (int j = 0; j < SIZE_OF_TABLE; ++j) {
			AnimalCard* cardToPrint = table[i][j].get();

			if (cardToPrint == nullptr)
				cout << "  |";
			else {
				cardToPrint->printRow(EvenOdd::ODD);
				cout << '|';
			}
		}

		cout << endl << "  |";

		for (int j = 0; j < SIZE_OF_TABLE; ++j) {
			AnimalCard* cardToPrint = table[i][j].get();

			if (cardToPrint == nullptr)
				cout << "  |";
			else {
				cardToPrint->printRow(EvenOdd::EVEN);
				cout << '|';
			}
		}

		cout << endl;
	}

	cout << endl << endl;
}

int Table::getTableSize() const { return SIZE_OF_TABLE; }

vector<int>& Table::getNumOfAnimals() { return numOfAnimals; }

void Table::setNumOfAnimals(vector<int> newList) { numOfAnimals = newList; }