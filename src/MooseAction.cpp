// fait par Jonathan Guillotte-Blouin

#include "MooseAction.h"

QueryResult MooseAction::query() {
	cout << endl << "Carte MooseAction..." << endl;

	return QueryResult();
}

bool MooseAction::perform(Table& table, Player* player, QueryResult qResult) {
	auto players = table.getPlayers();
	string tmpAnimal = players[0].get()->getSecretAnimal();

	for (int i = 0; i < players.size(); ++i) {
		int nextPlayer = (i + 1) % players.size();

		tmpAnimal = players[nextPlayer].get()->swapSecretAnimal(tmpAnimal);
	}

	return true;
}