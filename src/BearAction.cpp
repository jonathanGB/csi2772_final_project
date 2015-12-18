// fait par Jonathan Guillotte-Blouin

#include "BearAction.h"

QueryResult BearAction::query() {
	cout << endl << "Carte BearAction..." << endl;
	cout << "Avec quel joueur voulez-vous echange de main? ";

	string playerName;
	cin >> playerName;

	return QueryResult(playerName);
}

bool BearAction::perform(Table& table, Player* player, QueryResult qResult) {
	auto players = table.getPlayers();
	string otherPlayerName = qResult.getOtherPlayer();
	Player* otherPlayer;

	if ((otherPlayer = validPlayerName(otherPlayerName, player, players)) == nullptr)
		return false;

	player->swapHand(otherPlayer);
	return true;
}