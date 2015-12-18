// fait par Jonathan Guillotte-Blouin

#include "AnimalCardFactory.h"

char AnimalCardFactory::getAnimal(int index) const {
	if (index == 0)
		return 'b';
	else if (index == 1)
		return 'd';
	else if (index == 2)
		return 'h';
	else if (index == 3)
		return 'm';
	else if (index == 4)
		return 'w';
	else
		return 'x';
}

int AnimalCardFactory::getSecondIndex(int index) const {
	int possibility1, possibility2;

	switch (index) {
	case 0:
		possibility1 = 1;
		possibility2 = 2;
		break;

	case 1:
		possibility1 = 0;
		possibility2 = 3;
		break;

	case 2:
		possibility1 = 0;
		possibility2 = 3;
		break;

	case 3:
		possibility1 = 1;
		possibility2 = 2;
		break;

	default:
		throw IllegalPlacement("L'index devrait etre entre 0 et 3!");
	}

	return rand() % 2 == 0 ?
		possibility1 :
		possibility2 ;

}

void AnimalCardFactory::generateCards() {
	// 1 Joker
	deck.add(shared_ptr<AnimalCard>(new Joker()));


	// 15 ActionCards
	for (int i = 0; i < 3; ++i) {
		deck.add(shared_ptr<AnimalCard>(new BearAction()));
		deck.add(shared_ptr<AnimalCard>(new DeerAction()));
		deck.add(shared_ptr<AnimalCard>(new HareAction()));
		deck.add(shared_ptr<AnimalCard>(new MooseAction()));
		deck.add(shared_ptr<AnimalCard>(new WolfAction()));
	}


	// 5 NoSplit
	deck.add(shared_ptr<AnimalCard>(new NoSplit('b')));
	deck.add(shared_ptr<AnimalCard>(new NoSplit('d')));
	deck.add(shared_ptr<AnimalCard>(new NoSplit('h')));
	deck.add(shared_ptr<AnimalCard>(new NoSplit('m')));
	deck.add(shared_ptr<AnimalCard>(new NoSplit('w')));


	// 20 SplitThree
	int randomIndex;
	int secondIndex;

	srand(time(NULL));

	for (int i = 0; i < 4; ++i) {
		int inc = i + 1;

		for (int ctr = 0, j = i; ctr < 5; j = (j + inc) % 5, ++ctr) {
			randomIndex = rand() % 4;
			secondIndex = getSecondIndex(randomIndex);

			char card[4] = { '\0', '\0', '\0', '\0' };
			card[randomIndex] = getAnimal(j);
			card[secondIndex] = card[randomIndex];

			int k = (j + inc) % 5;
			int l = (k + inc) % 5;

			vector<char> otherAnimals = { getAnimal(k), getAnimal(l) };

			for (int m = 0; m < 4; ++m) {
				if (!card[m]) {
					card[m] = otherAnimals.back();
					otherAnimals.pop_back();
				}
			}

			deck.add(shared_ptr<AnimalCard>(new SplitThree(card)));
		}
	}

	// seed pour le shuffle
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// 10 SplitTwo
	char animals[5] = { 'b', 'd', 'h', 'm', 'w' };

	for (int i = 0; i < 2; ++i) {
		shuffle(begin(animals), end(animals), default_random_engine(seed));

		for (int j = 0; j < 5; ++j) {
			randomIndex = rand() % 4;
			secondIndex = getSecondIndex(randomIndex);

			char card[4] = { '\0', '\0', '\0', '\0' };
			card[randomIndex] = getAnimal(j);
			card[secondIndex] = card[randomIndex];

			int k = (j + 1) % 5;

			for (int m = 0; m < 4; ++m) {
				if (!card[m])
					card[m] = getAnimal(k);
			}

			deck.add(shared_ptr<AnimalCard>(new SplitTwo(card)));
		}
	}

	int thirdIndex, fourthIndex;

	// 15 SplitFour
	for (int i = 0; i < 3; ++i) {
		shuffle(begin(animals), end(animals), default_random_engine(seed));

		for (int j = 0; j < 5; ++j) {
			randomIndex = rand() % 4;

			do
				secondIndex = rand() % 4;
			while (secondIndex == randomIndex);

			do
				thirdIndex = rand() % 4;
			while (thirdIndex == randomIndex || thirdIndex == secondIndex);

			do
				fourthIndex = rand() % 4;
			while (fourthIndex == randomIndex || fourthIndex == secondIndex || fourthIndex == thirdIndex);

			char card[4];
			card[randomIndex] = getAnimal(j);
			card[secondIndex] = getAnimal((j + 1) % 5);
			card[thirdIndex] = getAnimal((j + 2) % 5);
			card[fourthIndex] = getAnimal((j + 3) % 5);

			deck.add(shared_ptr<AnimalCard>(new SplitFour(card)));
		}
	}


	
	// brasser les cartes
	shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

AnimalCardFactory::AnimalCardFactory() {
	generateCards();
}

AnimalCardFactory* AnimalCardFactory::getFactory() { return new AnimalCardFactory(); }

Deck<shared_ptr<AnimalCard>> AnimalCardFactory::getDeck() { return deck; }