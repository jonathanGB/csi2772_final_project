#ifndef HARE_ACTION_H
#define HARE_ACTION_H

// fait par Jonathan Guillotte-Blouin

#include "ActionCard.h"

class HareAction : public ActionCard {
public:
	HareAction() : ActionCard('H') {};

	QueryResult query();
	bool perform(Table&, Player*, QueryResult);
};

#endif