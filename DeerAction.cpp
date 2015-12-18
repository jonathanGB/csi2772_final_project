// fait par Jonathan Guillotte-Blouin

#include "DeerAction.h"

QueryResult DeerAction::query() {
	cout << endl << "Carte DeerAction..." << endl;
	cout << "Avec quel joueur voulez-vous echange de carte objectif? ";

	string playerName;
	cin >> playerName;

	return QueryResult(playerName);
}

bool DeerAction::perform(Table& table, Player* player, QueryResult qResult) {
	auto players = table.getPlayers();
	string otherPlayerName = qResult.getOtherPlayer();
	Player* otherPlayer;

	if ((otherPlayer = validPlayerName(otherPlayerName, player, players)) == nullptr)
		return false;

	string otherPlayerAnimal = otherPlayer->swapSecretAnimal(player->getSecretAnimal());
	player->swapSecretAnimal(otherPlayerAnimal);
	return true;
}