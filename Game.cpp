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


    // careful while changing i
    for (int i=1; i<=numRounds; i++){
        Round* round = new Round(i, players);
        round->start();
    }
}
