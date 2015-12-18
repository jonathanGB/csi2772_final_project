#ifndef ILLEGAL_PLACEMENT_H
#define ILLEGAL_PLACEMENT_H

// fait par Jonathan Guillotte-Blouin

#include <iostream>
#include <string>

using namespace std;

class IllegalPlacement {
public:
	IllegalPlacement(string errorMessage) { cout << errorMessage << endl; }
};

#endif