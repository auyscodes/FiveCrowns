//
// Created by nbhat on 9/15/2019.
//

#include "Game.h"
#include "Deck.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"
#include "DataLayer.h"
#include "Serialization.h"


Game::Game()
{
	dataLayer = NULL; // value is intialized when starting a new game or loading a game 
}

vector<Player*>* Game::createPlayers(int& startPlayerIndex, int&humanPlayerIndex, int&computerPlayerIndex) {
	
    Human* human = new Human();
    human->setName(new string("computer1"));
	human->setSaveGameCallback(this);
    Computer* human1 = new Computer();
    human1->setName(new string("computer2"));

    vector<Player*> * players = new vector<Player*>();
    players->insert(players->begin(), human1);
    players->insert(players->begin(), human);

	startPlayerIndex = 0; // since firstPlayer is human
	humanPlayerIndex = 0;
	computerPlayerIndex = 1;
	return players;
}

void Game::askUser() {
	cout << "1. Start new game" << endl;
	cout << "2. Load saved game" << endl;
	int option;
	do {
		cout << "Enter option (1 or 2): ";
		cin >> option;
	} while (option < 1 && option>2);
	switch (option) {
	case 1: {
		startNew();
	}
		  break;
	case 2: {
		string filename;
		do {
			cin.clear();
			cin.ignore();
			cout << "Enter file name: ";
			getline(cin, filename);
		} while (filename.empty());
		
		loadGame(filename);
	}
		  break;
	default:
		break;
	}
}

void Game::loadGame(string filename) {
	
	dataLayer = Serialization::loadFromFile( filename);
	cout << "back in game " << endl;
	cout << " hand " << dataLayer->getPlayers()->front()->getHand()->toString() << endl;
	for (int i = dataLayer->getRound(); i <= numRounds; i++) {
		Round* round = new Round(i, dataLayer);
		dataLayer->setRound(i);
		round->startGame();
	}

}
void Game::startNew() {
	int startPlayerIndex;
	int humanPlayerIndex;
	int computerPlayerIndex;
	vector<Player*>* players = createPlayers(startPlayerIndex, humanPlayerIndex, computerPlayerIndex);
	int nextPlayer = toss(startPlayerIndex, players->size());
	dataLayer = new DataLayer(players, nextPlayer, startingAtRound, humanPlayerIndex, computerPlayerIndex);
	for (int i = 1; i <= numRounds; i++) {
		Round* round = new Round(i, dataLayer);
		dataLayer->setRound(i);
		round->startGame();

	}
}
void Game::start() {
    // start method takes in parameter new or load
    // if load then needs to load everything from file and put in respective objects :- drawpile, discard pile, next player, human score, computer score, etc.
    // file input validation needs to be checked especially that discard pile should never be empty when saving game state as loading game logic depends on it
	

    // careful while changing i
	askUser();
	

	displayWinnerAndLoserScore();

}
bool Game::saveGame(string filename)
{
	cout << "in game saving" << endl;
	Serialization::saveInFile(dataLayer, filename);
	return false;
}
// works only for two players correctly
void Game::displayWinnerAndLoserScore() {

	cout << "\n-------------------------------Game Ended ----------------------------------\n";
	cout << "Final scores :- " << endl;
	string p1_name = dataLayer->getPlayers()->at(0)->getName();
	string p2_name = dataLayer->getPlayers()->at(1)->getName();
	int p1_score = dataLayer->getPlayers()->at(0)->getScore();
	int p2_score = dataLayer->getPlayers()->at(1)->getScore();
	cout << p1_name  << " 's score : " << p1_score << endl;
	cout << p2_name << " 's score : " << p2_score << endl;
	if (p1_score == p2_score) {
		cout << "Game Draw " << endl;
	}
	else if (p1_score < p2_score) {
		cout << p1_name << " won" << endl;
	}
	else {
		cout << p2_name << " won" << endl;
	}
	
}



int Game::toss(int startPlayerIndex, int totalPlayers) {
	cout << "--------Toss--------- " << endl;
	cout << "Press 0 for tail or 1 for head : ";
	int option;
	do {
		cin.clear();

		cin >> option;
		if (option > 1 && option < 0) cout << "Wrong option entered. Enter again : ";
	} while (option < 0 && option >1);
	// int max = dataLayer->getPlayers()->size() - 1;
	int	max = 1; // head
	int min = 0; // tail
	int toss = rand() % (max - min + 1) + min;
	if (toss == option) {
		int first_player;
		cin.clear();
		cin.ignore();
		cout << "Press 1 to go first / any other number to go last : ";
		cin >> first_player;
		if (first_player == 1) {
			return startPlayerIndex;
			cout << "You are going first " << endl;
		}
		cout << "Computer is going first " << endl;
		return ++startPlayerIndex% totalPlayers;
		
	}
	cout << " Lost toss, computer decided to go first " << endl;
	// computer always goes first
	return ++startPlayerIndex % totalPlayers; // !!!!!!!!!!!!!!!!!!!!! hardcoded 


}