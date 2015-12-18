#ifndef MOOSE_ACTION_H
#define MOOSE_ACTION_H

// fait par Jonathan Guillotte-Blouin

#include "ActionCard.h"

class MooseAction : public ActionCard {
public:
	MooseAction() : ActionCard('M') {};

	QueryResult query();
	bool perform(Table&, Player*, QueryResult);
};

#endif