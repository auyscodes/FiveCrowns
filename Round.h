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

class Round {
public:

	
    Round( DataLayer* dataLayer);
    void deal();
	void startGame();
    int getRoundNumber(){
        return this->numCardsToDeal - 2; // in round 1 we deal 3 cards
    }
	void tempPrinter(vector<vector<CardInterface*>>& cardsArrgnment);
    void collectCardsFromPiles();
    bool tryGoOut(Hand* hand, int & minScore, vector<vector<CardInterface*>> & arrgnMnt);
	// destructor not needed 
private:

    int numCardsToDeal;
    const int startRound = 1;
	int playersGoneOut = 0; // 
    DataLayer* dataLayer;
    

    int getScore(Card* card);

    string convertNumCardsToDealToWildCards(int numCardsToDeal);
	
    bool checkGoOutPossible(CardCollection* hand, int& score, vector<vector<CardInterface*>>& minBranch);

	// this functionality is unused at the time
	void notifyOtherPlayers(vector<Player*>* players); // notifies other players that one player has successfully gone out
    

	void forceGoOut(CardCollection* hand, int& score, vector<vector<CardInterface*>>& cardsArgmnt);
	

};


#endif //FIVECROWNS_ROUND_H
