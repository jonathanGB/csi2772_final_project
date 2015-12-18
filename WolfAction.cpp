// fait par Jonathan Guillotte-Blouin

#include "WolfAction.h"

QueryResult WolfAction::query() {
	cout << endl << "Carte WolfAction..." << endl;
	cout << "Donnez les coordonnes de la carte que vous voulez ajouter a votre deck (i.e. 10 23) ";

	int cardRow, cardCol;
	cin >> cardRow >> cardCol;

	return QueryResult(cardRow, cardCol);
}

bool WolfAction::perform(Table& table, Player* player, QueryResult qResult)
{
	shared_ptr<AnimalCard> removedPtr = table.get(qResult.getCardRow(), qResult.getCardCol());

	if (removedPtr.get() == nullptr)
		return false;

	player->addCard(removedPtr);
	table.pickAt(qResult.getCardRow(), qResult.getCardCol());

	return true;
}