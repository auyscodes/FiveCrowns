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
#include "DataLayer.h"

class UI;
#include <map>

class Round: public IGoOut {
public:
//    Round(int round, vector<Player*>& players){
//        this->numCardsToDeal = round + 2; // in round 1 we deal 3 cards
//        this->players = players;
//    }
    Round(int round, DataLayer* dataLayer);

// Round(int round, vector<Player*>& players);
    // Round(int round, map<string, Player*> & players);
    void start();
    void deal();
//    Player* getNextPlayer();
    int getRoundNumber(){
        return this->numCardsToDeal - 2; // in round 1 we deal 3 cards
    }
     vector<Player*> * getPlayers(); // function might not be necessary
//    map<string, Player*>& getPlayers();
    void collectCardsFromPiles();
    void goOut(Hand* hand);
private:
    int numCardsToDeal;
    const int startRound = 1;
//    vector<Player*> players;
    // map<string, Player*> players;
    DataLayer* dataLayer;
    bool onePlayerHasGoneOut;
    void setGoOutListener();

    int getScore(Card* card);
    string convertNumCardsToDealToWildCards(int numCardsToDeal);
    bool checkGoOutPossible(CardCollection* hand);


    int countScore(CardCollection *hand);
};


#endif //FIVECROWNS_ROUND_H
