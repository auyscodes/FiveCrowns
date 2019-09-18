//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_ROUND_H
#define FIVECROWNS_ROUND_H


#include "Player.h"
#include "DrawPile.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "CardPile.h"
#include "UI.h"
 class UI;
#include <map>

class Round {
public:
//    Round(int round, vector<Player*>& players){
//        this->numCardsToDeal = round + 2; // in round 1 we deal 3 cards
//        this->players = players;
//    }
    Round(int round, map<string, Player*> & players);
    void start();
    void deal();
//    Player* getNextPlayer();
    int getRoundNumber(){
        return this->numCardsToDeal - 2; // in round 1 we deal 3 cards
    }
    // vector<Player*> & getPlayers();
    map<string, Player*>& getPlayers();
    void collectCardsFromPiles();
private:
    int numCardsToDeal;
    const int startRound = 3;
    // vector<Player*> players;
    map<string, Player*> players;

};


#endif //FIVECROWNS_ROUND_H
