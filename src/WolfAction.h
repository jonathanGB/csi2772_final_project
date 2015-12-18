#ifndef WOLFE_ACTION_H
#define WOLFE_ACTION_H

// fait par Jonathan Guillotte-Blouin

#include "ActionCard.h"

class WolfAction : public ActionCard {
public:
	WolfAction() : ActionCard('W') {};

	QueryResult query();
	bool perform(Table&, Player*, QueryResult);
};

#endif