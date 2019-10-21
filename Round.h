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
#include "DataLayer.h"


#include <map>

class Round: public IGoOut {
public:

	void tempPrinter(vector<vector<CardInterface*>>& cardsArrgnment);
    Round(int round, DataLayer* dataLayer);
    void start();
    void deal();
    int getRoundNumber(){
        return this->numCardsToDeal - 2; // in round 1 we deal 3 cards
    }
     vector<Player*> * getPlayers(); // function might not be necessary
    void collectCardsFromPiles();
    bool tryGoOut(Hand* hand, int & minScore, vector<vector<CardInterface*>> & arrgnMnt);
    // cardcollection size should not be less than 3
    // normal should be sorted by value
	void startGame(); // added might need to remove later if doesn't work out
	~Round();

private:
    int numCardsToDeal;
    const int startRound = 1;
    DataLayer* dataLayer;
    int playersGoneOut = 0;
    void setGoOutListener();

    int getScore(Card* card);
    string convertNumCardsToDealToWildCards(int numCardsToDeal);
	
    bool checkGoOutPossible(CardCollection* hand, int& score, vector<vector<CardInterface*>>& minBranch);

	void notifyOtherPlayers(vector<Player*>* players); // notifies other players that one player has successfully gone out
    

	void forceGoOut(CardCollection* hand, int& score, vector<vector<CardInterface*>>& cardsArgmnt);
	

};


#endif //FIVECROWNS_ROUND_H
