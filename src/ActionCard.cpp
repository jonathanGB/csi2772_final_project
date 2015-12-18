// fait par Jonathan Guillotte-Blouin

#include "ActionCard.h"

string QueryResult::getOtherPlayer() const { return otherPlayer; }
int QueryResult::getCardRow() const { return cardRow; }
int QueryResult::getCardCol() const { return cardCol; }
int QueryResult::getNewRow() const { return newRow; }
int QueryResult::getNewCol() const { return newCol; }

Player* ActionCard::validPlayerName(string playerName, Player* currPlayer, vector<shared_ptr<Player>>& players) const {
	Player* otherPlayer = nullptr;

	for (int i = 0; i < players.size(); ++i) {
		if (currPlayer != players[i].get() && playerName == players[i].get()->getName()) {
			otherPlayer = players[i].get();
			break;
		}
	}

	return otherPlayer;
}