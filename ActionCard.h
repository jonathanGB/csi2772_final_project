#ifndef ACTION_CARD_H
#define ACTION_CARD_H

// fait par Jonathan Guillotte-Blouin

#include "NoSplit.h"
#include "Table.h"
#include "Player.h"

class QueryResult {
private:
	// BearAction et DeerAction
	string otherPlayer;

	// HareAction et WolfAction
	int cardRow, cardCol;

	// HareAction
	int newRow, newCol;

public:
	QueryResult() = default;
	QueryResult(string player2) : // appel de BearAction et DeerAction
		otherPlayer(player2) {};
	QueryResult(int row, int col) : // appel de WolfAction
		cardRow(row), cardCol(col) {};
	QueryResult(int row1, int col1, int row2, int col2) : // appel de HareAction
		cardRow(row1), cardCol(col1), newRow(row2), newCol(col2) {};

	string getOtherPlayer() const;
	int getCardRow() const;
	int getCardCol() const;
	int getNewRow() const;
	int getNewCol() const;
};

class ActionCard : public NoSplit {
protected:
	Player* validPlayerName(string, Player*, vector<shared_ptr<Player>>&) const;

public:
	ActionCard(char cardContent) : NoSplit(cardContent) {};

	virtual QueryResult query() = 0;
	virtual bool perform(Table&, Player*, QueryResult) = 0;
};

#endif