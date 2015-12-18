// fait par Jonathan Guillotte-Blouin

#include "Joker.h" 
#include "SplitTwo.h"
#include "SplitThree.h"
#include "SplitFour.h"
#include "WolfAction.h"
#include "Table.h"
#include "Hand.h"
#include "BearAction.h"
#include "Player.h"
#include "Deck.h"
#include "AnimalCardFactory.h"


int main2(void) {
	/* Test des Cards */

	// Test de NoSplit
	NoSplit nosplit('j');

	nosplit.setOrientation(Orientation::DOWN);
	nosplit.printRow(EvenOdd::ODD);
	cout << endl << endl;


	// Test de SplitTwo
	char arr[4] = { 't', 't', 'k', 'k'};
	SplitTwo splittwo(arr);

	splittwo.printRow(EvenOdd::ODD);
	cout << endl;
	splittwo.setOrientation(Orientation::DOWN);
	splittwo.printRow(EvenOdd::ODD);
	cout << endl;
	splittwo.printRow(EvenOdd::EVEN);
	cout << endl << endl;


	// Test de SplitThree
	char arr2[4] = {'i', 'i', 'm', 'n'};
	SplitThree splitthree(arr2);

	splitthree.printRow(EvenOdd::ODD);
	cout << endl;
	splitthree.setOrientation(Orientation::DOWN);
	splitthree.printRow(EvenOdd::ODD);
	cout << endl;
	splitthree.printRow(EvenOdd::EVEN);
	cout << endl << splitthree.get("TOP", "RIGHT") << endl << endl;


	// Test de SplitFour
	char arr3[4] = { 'd', 'c', 'l', 'k' };
	SplitFour splitfour(arr3);

	splitfour.printRow(EvenOdd::ODD);
	cout << endl;
	splitfour.setOrientation(Orientation::DOWN);
	splitfour.printRow(EvenOdd::ODD);
	cout << endl;
	splitfour.printRow(EvenOdd::EVEN);
	cout << endl << endl;


	// Test de xyzAction
	WolfAction b1;

	b1.printRow(EvenOdd::ODD);
	cout << endl;
	b1.setOrientation(Orientation::DOWN);
	b1.printRow(EvenOdd::ODD);
	cout << endl;
	b1.printRow(EvenOdd::EVEN);
	cout << endl << endl;

	char arr4[4] = { 'm', 'm', 'b', 'b' };
	char arr5[4] = { 'm', 'w', 'm', 'h' };
	char arr6[4] = { 'w', 'w', 'h', 'm' };
	string animal1 = "Bear";
	shared_ptr<AnimalCard> ptr(new SplitTwo(arr4));
	shared_ptr<AnimalCard> ptr2(new SplitThree(arr5));
	shared_ptr<AnimalCard> ptr3(new SplitThree(arr6));
	shared_ptr<AnimalCard> ptr4(new NoSplit('m'));
	shared_ptr<AnimalCard> ptr5(new Joker());
	shared_ptr<AnimalCard> ptr6(new WolfAction());
	Table table;
	try {
		int val = table.addAt(ptr, 52, 51);
		cout << val << endl;
		val = table.addAt(ptr2, 51, 51);
		cout << val << endl;
		val = table.addAt(ptr3, 51, 52);
		cout << val << endl;
		val = table.addAt(ptr4, 51, 53);
		cout << val << endl;
		val = table.addAt(ptr5, 51, 54);
		cout << val << endl;
		table.pickAt(51, 54);
		val = table.addAt(ptr6, 51, 54);
		table.get(51, 54).get()->printRow(EvenOdd::ODD);
		cout << val << endl;
		bool winornot = table.win(animal1);
		cout << winornot;
		table.pickAt(52, 51);
		winornot = table.win(animal1);
		cout << winornot;

		
		/* test de hand*/

		char carte1[4] = { 'm', 'w', 'b', 'b' };
		char carte2[4] = { 'h', 'w', 'm', 'h' };
		char carte3[4] = { 'w', 'w', 'h', 'm' };
		shared_ptr<AnimalCard> carteptr1(new SplitThree(carte1));
		shared_ptr<AnimalCard> carteptr2(new SplitFour(carte2));
		shared_ptr<AnimalCard> carteptr3(new SplitThree(carte3));
		shared_ptr<AnimalCard> carteptr4(new BearAction());
		
		Hand hand1;
		hand1 += ptr;
		hand1 += ptr2;
		cout << endl << hand1.noCards() << endl;
		hand1 -= ptr;
		cout << hand1.noCards() << endl;
		//hand1 -= ptr;
		//cout << "hihi" << hand1.noCards() << endl;
		//hand1 += ptr;
		hand1[0].get()->printRow(EvenOdd::ODD);
		cout << endl << endl;
		hand1.printHand();
		cout << endl;
		Hand hand2 = hand1;
		hand2.printHand();

		Hand hand3;
		hand3 += carteptr1;
		hand3 += carteptr2;
		hand3 += carteptr3;
		hand3 += carteptr4;
		cout << endl;
		hand3.printHand();
		cout << endl;
		hand3[2].get()->printRow(EvenOdd::EVEN);
		cout << endl << endl;


		/* test player */
		Player p1("Jonathan", "Bear", hand3);
		p1.printHand();
		string datAnimal("Wolf");
		p1.swapSecretAnimal(datAnimal);
		cout << p1.getSecretAnimal() << endl;


		/* test deck */
		Deck<shared_ptr<AnimalCard>> test;
		test.add(carteptr1);
		test.add(carteptr2);
		shared_ptr<AnimalCard> lool = test.draw();
		lool.get()->setOrientation(Orientation::DOWN);
		lool.get()->printRow(EvenOdd::EVEN);
		cout << endl << endl;

		/* Test AnimalCardFactory */
		AnimalCardFactory* ptrr = AnimalCardFactory::getFactory();
		Deck<shared_ptr<AnimalCard>> decks = ptrr->getDeck();
		AnimalCard* card;
		int numOfCardsCreated = 0;
		cout << endl << "15 SplitFour" << endl << endl;
		while ((card = decks.draw().get()) != nullptr) {
			if (numOfCardsCreated == 15)
				cout << endl << "10 SplitTwo" << endl << endl;
			else if (numOfCardsCreated == 25)
				cout << endl << "20 SplitThree" << endl << endl;
			else if (numOfCardsCreated == 45)
				cout << endl << "5 NoSplit" << endl << endl;
			else if (numOfCardsCreated == 50)
				cout << endl << "15 ActionCard" << endl << endl;
			else if (numOfCardsCreated == 65)
				cout << endl << "The joker" << endl << endl;

			numOfCardsCreated++;
			card->printRow(EvenOdd::ODD);
			cout << endl;
			card->printRow(EvenOdd::EVEN);
			cout << endl << endl;
		}

		cout << "Num of cards created: " << numOfCardsCreated << endl;
	}
	catch (IllegalPlacement) {}
	catch (MissingCard) {};

	system("PAUSE");
	return 0;
}