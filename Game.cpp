//
// Created by nbhat on 9/15/2019.
//

#include "Game.h"
#include "Deck.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"
#include "DataLayer.h"

void Game::onStart() {
    dataLayer = new DataLayer();
    // for loop above not needed
    createPlayers();
}
void Game::createPlayers() {
    Computer* human = new Computer();
    human->setName(new string("computer1"));
//    Computer* computer = new Computer();
//    computer->setName("computer");
    Computer* human1 = new Computer();
    human1->setName(new string("computer2"));


//    players.insert(players.begin(), new Computer());
//    players.insert(players.begin(), new Human());
//    players["Human"] = new Human();
//    players["Computer"] = new Computer();
    vector<Player*> * players = new vector<Player*>();
    players->insert(players->begin(), human1);
    players->insert(players->begin(), human);
    dataLayer->setPlayers(players);
    // instead of this make player class save name
    // maybe even score

}

void Game::start() {
    onStart();
    // start method takes in parameter new or load
    // if load then needs to load everything from file and put in respective objects :- drawpile, discard pile, next player, human score, computer score, etc.
    // file input validation needs to be checked especially that discard pile should never be empty when saving game state as loading game logic depends on it


    // careful while changing i
    for (int i=1;i<=numRounds;i++){
        Round* round = new Round(i, dataLayer);
        round->startGame();
    }
	

	displayWinnerAndLoserScore();
//    for (int i=1; i<=numRounds; i++){
//        Round* round = new Round(i, players);
//        round->start();
//    }
}
void Game::displayWinnerAndLoserScore() {
	
	
}
