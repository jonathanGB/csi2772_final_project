// fait par Jonathan Guillotte-Blouin

#include "HareAction.h"

QueryResult HareAction::query() {
	cout << endl << "Carte HareAction..." << endl;
	cout << "Donnez les coordonnes de la carte que vous voulez deplacer (i.e. 10 23) ";

	int cardRow, cardCol, newRow, newCol;
	cin >> cardRow >> cardCol;

	cout << endl << "Donnez maintenant les coordonnees du nouvel emplacement de la carte ";
	cin >> newRow >> newCol;

	return QueryResult(cardRow, cardCol, newRow, newCol);
}

bool HareAction::perform(Table& table, Player* player, QueryResult qResult) {
	shared_ptr<AnimalCard> removedPtr = table.get(qResult.getCardRow(), qResult.getCardCol());

	if (removedPtr.get() == nullptr || table.get(qResult.getNewRow(), qResult.getNewCol()).get() != nullptr)
		return false;

	try {
		table.addAt(removedPtr, qResult.getNewRow(), qResult.getNewCol());
		table.pickAt(qResult.getCardRow(), qResult.getCardCol());
		return true;
	}
	catch (IllegalPlacement) {
		return false;
	};
}