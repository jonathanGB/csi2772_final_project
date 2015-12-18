#ifndef BEAR_ACTION_H
#define BEAR_ACTION_H

// fait par Jonathan Guillotte-Blouin

#include "ActionCard.h"

class BearAction : public ActionCard {
public:
	BearAction() : ActionCard('B') {};

	QueryResult query();
	bool perform(Table&, Player*, QueryResult);
};

#endif