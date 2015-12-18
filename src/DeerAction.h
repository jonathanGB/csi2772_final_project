#ifndef DEER_ACTION_H
#define DEER_ACTION_H

// fait par Jonathan Guillotte-Blouin

#include "ActionCard.h"

class DeerAction : public ActionCard {
public:
	DeerAction() : ActionCard('D') {};

	QueryResult query();
	bool perform(Table&, Player*, QueryResult);
};

#endif