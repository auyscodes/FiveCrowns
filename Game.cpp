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
	dataLayer = NULL; // I feel this is unnecessary though
}

vector<Player*>* Game::createPlayers(int& startPlayerIndex, int&humanPlayerIndex, int&computerPlayerIndex) {
	
    Human* human = new Human();
    human->setName(new string("Human"));
	human->setSaveGameCallback(this);
    Computer* computer = new Computer();
    computer->setName(new string("Computer"));

    vector<Player*> * players = new vector<Player*>();
    players->insert(players->begin(), computer);
    players->insert(players->begin(), human);

	
	humanPlayerIndex = 0;
	computerPlayerIndex = 1;
	startPlayerIndex = humanPlayerIndex;
	return players;
}

void Game::askUser() {
	cout << "1. Start new game" << endl;
	cout << "2. Load saved game" << endl;
	int option;
	cin >> option;
	
	while (!cin || option <1 || option>2) {
			cout << "Please enter valid integer option: ";
			cin.clear();
			cin.ignore();
			cin >> option;
			
	}
		
	
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
		exit(EXIT_FAILURE);
	}
}

void Game::loadGame(string filename) {
	
	dataLayer = Serialization::loadFromFile( filename);
	cout << "back in game " << endl;
	cout << " hand " << dataLayer->getPlayers()->front()->getHand()->toString() << endl;
	dataLayer->turnIsLoadOn(); 
	for (int i = dataLayer->getRound(); i <= numRounds; i++) {
		dataLayer->setRound(i);
		Round* round = new Round( dataLayer);
		
		round->startGame();
	}

}

void Game::startNew() {
	const int startingAtRound = 1; // startRound
	int startPlayerIndex;
	int humanPlayerIndex;
	int computerPlayerIndex;
	vector<Player*>* players = createPlayers(startPlayerIndex, humanPlayerIndex, computerPlayerIndex);
	int nextPlayer = toss(humanPlayerIndex, computerPlayerIndex);
	dataLayer = new DataLayer(players, nextPlayer, startingAtRound, humanPlayerIndex, computerPlayerIndex);
	dataLayer->setCardCollection(); // do not forget this
	for (int i = 1; i <= numRounds; i++) {
		dataLayer->setRound(i);
		Round* round = new Round( dataLayer);
		
		round->startGame();

	}
}
void Game::start() {
    
	askUser();
	

	displayWinnerAndLoserScore();

}
bool Game::saveGame(string filename)
{
	
	return Serialization::saveInFile(dataLayer, filename);
	
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



int Game::toss(int humanPlayerIndex, int computerPlayerIndex) {
	cout << "--------Toss--------- " << endl;
	cout << "Press 0 for tail or 1 for head : ";
	int option;
	cin >> option;

	while (!cin || option < 0 || option>1) {
		cout << "Please enter valid integer option: ";
		cin.clear();
		cin.ignore();
		cin >> option;

	}
	int	max = 1; // head
	int min = 0; // tail
	int toss = rand() % (max - min + 1) + min;
	if (toss == option) {
		cout << "Human won the toss" << endl;
		return humanPlayerIndex;
	}
	cout << "Computer won the toss" << endl;
	return computerPlayerIndex ;
	


}
Game::~Game()
{
	delete dataLayer;
}