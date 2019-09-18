//
// Created by nbhat on 9/15/2019.
//

#include "Game.h"
#include "Deck.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"

void Game::onStart() {

    // for loop above not needed
    createPlayers();
}
void Game::createPlayers() {

//    players.insert(players.begin(), new Computer());
//    players.insert(players.begin(), new Human());
    players["Human"] = new Human();
    players["Computer"] = new Computer();

}

void Game::start() {
    onStart();
    // start method takes in parameter new or load
    // if load then needs to load everything from file and put in respective objects :- drawpile, discard pile, next player, human score, computer score, etc.
    // file input validation needs to be checked especially that discard pile should never be empty when saving game state as loading game logic depends on it


    // careful while changing i
    for (int i=1; i<=numRounds; i++){
        Round* round = new Round(i, players);
        round->start();
    }
}
