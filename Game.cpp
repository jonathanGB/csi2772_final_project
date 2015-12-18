// fait par Jonathan Guillotte-Blouin

#include <fstream>
#include <sstream>
#include "Table.h"
#include "Hand.h"
#include "Player.h"
#include "Deck.h"
#include "AnimalCardFactory.h"
#include "AnimalCard.h"

// savoir si l'un des joueurs a gagne
int won(Table& table, vector<shared_ptr<Player>>& players, int numOfPlayers) {
	for (int i = 0; i < numOfPlayers; ++i) {
		string playerAnimal = players[i].get()->getSecretAnimal();

		if (table.win(playerAnimal))
			return i;
	}

	return -1;
}

shared_ptr<AnimalCard> createCard(char char1, char char2, char char3, char char4) {
	if (char1 == 'j')
		return shared_ptr<AnimalCard>(new Joker());
	else if (char1 == 'B')
		return shared_ptr<AnimalCard>(new BearAction());
	else if (char1 == 'D')
		return shared_ptr<AnimalCard>(new DeerAction());
	else if (char1 == 'H')
		return shared_ptr<AnimalCard>(new HareAction());
	else if (char1 == 'M')
		return shared_ptr<AnimalCard>(new MooseAction());
	else if (char1 == 'W')
		return shared_ptr<AnimalCard>(new WolfAction());
	else {
		vector<char> animals;
		char card[4] = { char1, char2, char3, char4 };
		
		animals.push_back(char1);

		if (char2 != char1)
			animals.push_back(char2);

		if (char3 != char1)
			animals.push_back(char3);

		if (char4 != char2 && char4 != char3)
			animals.push_back(char4);

		if (animals.size() == 1)
			return shared_ptr<AnimalCard>(new NoSplit(char1));
		else if (animals.size() == 2)
			return shared_ptr<AnimalCard>(new SplitTwo(card));
		else if (animals.size() == 3)
			return shared_ptr<AnimalCard>(new SplitThree(card));
		else 
			return shared_ptr<AnimalCard>(new SplitFour(card));
	}
}

void saveGame(Table& table, vector<shared_ptr<Player>>& players, Deck<shared_ptr<AnimalCard>>& deck) {
	ofstream gameFile;
	gameFile.open("gameFile.txt");
	
	const vector<int> numOfAnimals = table.getNumOfAnimals();

	gameFile << "currResults" << endl;

	for (int i = 0; i < numOfAnimals.size(); ++i)
		gameFile << numOfAnimals[i] << ' ';

	gameFile << endl;
	
	for (int i = 0; i < table.getTableSize(); ++i) {
		for (int j = 0; j < table.getTableSize(); ++j) {
			AnimalCard* ptr = table.get(i, j).get();

			if (ptr != nullptr && ptr->get("TOP", "LEFT") != 'c') {
				gameFile << "table" << endl;
				gameFile << i << ' ' << j << ' ' << ptr->get("TOP", "LEFT") << ' ' << ptr->get("TOP", "RIGHT") << ' ' << ptr->get("BOTTOM", "LEFT") << ' ' << ptr->get("BOTTOM", "RIGHT") << endl;
			}
		}
	}

	for (int i = 0; i < players.size(); ++i) {
		Player* player = players[i].get();

		gameFile << "player" << endl;
		gameFile << player->getName() << ' ' << player->getSecretAnimal() << ' ' << player->sizeOfHand() << endl;
	
		for (int j = 0, sizeHand = player->sizeOfHand(); j < sizeHand; ++j) {
			AnimalCard* card = player->pickCard(0).get();

			gameFile << card->get("TOP", "LEFT") << ' ' << card->get("TOP", "RIGHT") << ' ' << card->get("BOTTOM", "LEFT") << ' ' << card->get("BOTTOM", "RIGHT") << endl;
		}
	}

	gameFile << "deck" << endl;
	gameFile << deck.size() << endl;

	for (int i = 0; i < deck.size(); ++i) {
		AnimalCard* card = deck[i].get();

		gameFile << card->get("TOP", "LEFT") << ' ' << card->get("TOP", "RIGHT") << ' ' << card->get("BOTTOM", "LEFT") << ' ' << card->get("BOTTOM", "RIGHT") << endl;
	}

	gameFile.close();
}

void loadGame(Table& table, Deck<shared_ptr<AnimalCard>>& deck, int& numPlayers) {
	string line;
	ifstream gameFile;
	gameFile.open("gameFile.txt");

	while (getline(gameFile, line)) {
		if (line == "currResults") {
			int anim1, anim2, anim3, anim4, anim5;

			getline(gameFile, line);
			stringstream stream(line);

			stream >> anim1 >> anim2 >> anim3 >> anim4 >> anim5;

			table.setNumOfAnimals({ anim1, anim2, anim3, anim4, anim5 });
		}
		else if (line == "table") {
			int row, col;
			char char1, char2, char3, char4;

			getline(gameFile, line);
			stringstream stream(line);

			stream >> row >> col >> char1 >> char2 >> char3 >> char4;

			shared_ptr<AnimalCard> cardLoaded = createCard(char1, char2, char3, char4);
			table.addAt(cardLoaded, row, col, true);
		}
		else if (line == "player") {
			string name, animal;
			int numCards;

			getline(gameFile, line);
			stringstream stream(line);

			stream >> name >> animal >> numCards;

			shared_ptr<Player> newPlayer(new Player(name, animal));
			table.addPlayer(newPlayer);

			for (int i = 0; i < numCards; ++i) {
				char char1, char2, char3, char4;

				getline(gameFile, line);
				stringstream cardStream(line);

				cardStream >> char1 >> char2 >> char3 >> char4;

				newPlayer.get()->addCard(createCard(char1, char2, char3, char4));
			}

			numPlayers++;
		}
		else if (line == "deck") {
			int sizeDeck;

			getline(gameFile, line);
			stringstream stream(line);

			stream >> sizeDeck;

			for (int i = 0; i < sizeDeck; ++i) {
				char char1, char2, char3, char4;

				getline(gameFile, line);
				stringstream cardStream(line);

				cardStream >> char1 >> char2 >> char3 >> char4;

				deck.add(createCard(char1, char2, char3, char4));
			}
		}
	}

	gameFile.close();
}

int main(void) {
	cout << "BIENVENUE DANS LE JEU FIVE ANIMALS!!!" << endl;
	cout << "=====================================\n" << endl;

	cout << "Pour bien voir la table de jeu, veuillez changer les proprietes de la taille de la console pour qu'elle prenne le maximum d'espace." << endl;
	cout << "Aussi, veuillez mettre le buffer-width de la console a au moins 313" << endl << endl;
	
	int choixInput;

	do { // choix d'initialisation
		cout << "Choisissez comment commencer: " << endl;
		cout << "1. Recommencer la partie" << endl;
		cout << "2. Charger une partie existante" << endl;
		cin >> choixInput;
	} while (choixInput != 1 && choixInput != 2);


	Table table;
	Deck<shared_ptr<AnimalCard>> deck;
	vector<shared_ptr<Player>> players;
	int numPlayers = 0;

	if (choixInput == 1) { // nouvelle partie
		const int MIN_JOUEURS = 2;
		const int MAX_JOUEURS = 5;
		vector<string> animals = { "bear", "deer", "hare", "moose", "wolf" };

		AnimalCardFactory* factory = AnimalCardFactory::getFactory();
		deck = factory->getDeck();
		
		// brasser le vecteur d'animaux (qui seront assignes a chaque joueur comme animal objectif)
		srand(time(NULL));
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(animals.begin(), animals.end(), default_random_engine(seed));


		do { // initialiser les joueurs
			if (numPlayers++ >= MIN_JOUEURS) {
				cout << "\nVoulez-vous ajouter un joueur? O/N" << endl;
				char ajouterPlayer;
				cin >> ajouterPlayer;

				if (ajouterPlayer == 'n' || ajouterPlayer == 'N') {
					numPlayers--;
					break;
				}
			}

			cout << "\nQuel est le nom du joueur " << numPlayers << "?" << endl;
			string playerName;
			cin >> playerName;

			table.addPlayer(shared_ptr<Player>(new Player(playerName, animals.back())));
			animals.pop_back();
		} while (numPlayers < MAX_JOUEURS);

		cin.clear();

		players = table.getPlayers();

		// donner les 3 cartes a chaque joueur au debut
		for (int i = 0; i < numPlayers; ++i) {
			for (int j = 0; j < 3; ++j) 
				players[i].get()->addCard(deck.draw());
		}
	}
	else {
		loadGame(table, deck, numPlayers);
		players = table.getPlayers();
		cout << "\nPartie chargee!" << endl;
	}

	int winner = -1;

	// deroulement central du jeu, tant que personne n'a gagne
	do {
		int cardChosen = 0;

		for (int i = 0; i < numPlayers; ++i) {
			if (cardChosen != -1) {
				char displayTable;

				cout << "Voulez-vous imprimer la table? O/N" << endl;
				cin >> displayTable;

				if (displayTable == 'o' || displayTable == 'O')
					table.printTable();
			}

			players[i].get()->addCard(deck.draw());
			players[i].get()->printHand();

			do {
				cout << endl << "Choisissez la carte que vous voulez jouer! (i.e. le nombre indique) ou \"-1\" pour passer votre tour" << endl;
				cin >> cardChosen;
			} while (cardChosen < -1 || cardChosen >= players[i].get()->sizeOfHand());

			if (cardChosen == -1)
				cout << endl << "Tour passe!\n" << endl;
			else {
				cout << endl << "Carte choisie: " << cardChosen << endl;

				shared_ptr<AnimalCard> pickedCard = players[i].get()->pickCard(cardChosen);

				if (pickedCard.get()->isActionCard()) {
					ActionCard* actionCard = dynamic_pointer_cast<ActionCard>(pickedCard).get();
					QueryResult query;

					do
						query = actionCard->query();
					while (!actionCard->perform(table, players[i].get(), query));
				}
				else {
					int newRow, newCol, cardToDraw;
					char orientation;

					do {
						cout << "A quel coordonne desirez-vous placer la carte " << cardChosen << "? (par exemple 40 40) ";
						cin >> newRow >> newCol;
						cout << "Voulez-vous mettre votre carte a l'envers? O/N ";
						cin >> orientation;

						if (orientation == 'o' || orientation == 'O')
							pickedCard.get()->setOrientation(Orientation::DOWN);

						try {
							cardToDraw = table.addAt(pickedCard, newRow, newCol);
							break;
						}
						catch (IllegalPlacement) {};
					} while (true);

					for (int j = 0; j < cardToDraw; ++j)
						players[i].get()->addCard(deck.draw());

					cout << endl << "Ce jeu a appartie " << cardToDraw << " animaux!" << endl;
				}

				// verifier si un joueur a gagne
				if ((winner = won(table, players, numPlayers)) != -1) {
					cout << players[winner].get()->getName() << " a gagne!" << endl;
					cout << "Sa carte objectif etait: " << players[winner].get()->getSecretAnimal() << endl;
					break;
				}
			}
		}

		if (winner == -1) {
			cout << "Voulez-vous sauvegarder la partie? O/N ";
			char sauvegarderPartie;
			cin >> sauvegarderPartie;

			if (sauvegarderPartie == 'o' || sauvegarderPartie == 'O') {
				saveGame(table, players, deck);
				cout << "\nPartie sauvegardee!" << endl;
				break;
			}
		}
	} while (winner == -1);

	system("PAUSE");
	return 0;
}