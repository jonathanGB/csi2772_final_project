#ifndef DECK_H
#define DECK_H

// fait par Jonathan Guillotte-Blouin

#include <vector>
#include <memory>
#include "MissingCard.h"

using namespace std;

template <typename T>
class Deck : public vector<T> {
public:
	Deck() : vector() {};

	T draw();
	void add(T);
};

template<class T>
inline T Deck<T>::draw()
{
	if (size() > 0) {
		T returned = this->back();
		pop_back();

		return returned;
	}
	else
		return nullptr;
}

template<class T>
inline void Deck<T>::add(T elem) {
	this->push_back(elem);
}

#endif