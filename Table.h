#ifndef TABLE_H
#define TABLE_H

// fait par Jonathan Guillotte-Blouin

#include <memory>
#include <vector>
#include "StartCard.h"
#include "Player.h"

class Table {
private:
	static const int SIZE_OF_TABLE = 103;
	static const int NOMBRE_GAGNANT = 12;
	vector<shared_ptr<Player>> allPlayers;
	shared_ptr<AnimalCard> table[SIZE_OF_TABLE][SIZE_OF_TABLE];
	vector<int> numOfAnimals;

	int getAnimalMatch(int, int, AnimalCard*) const;
	bool animalFound(vector<char>&, char) const;
	void updateNumOfAnimals(shared_ptr<AnimalCard>, string);
	int getAnimalIndex(string);
	int getAnimalIndex(char);

public:
	Table();

	int addAt(shared_ptr<AnimalCard>, int, int, bool = false);
	shared_ptr<AnimalCard> pickAt(int row, int col);
	shared_ptr<AnimalCard> get(int row, int col) const;
	bool win(std::string& animal);
	void addPlayer(shared_ptr<Player>);
	vector<shared_ptr<Player>> getPlayers() const;
	void printTable() const;
	int getTableSize() const;
	vector<int>& getNumOfAnimals();
	void setNumOfAnimals(vector<int>);
};

#endif