//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_PLAYER_H
#define FIVECROWNS_PLAYER_H


#include "Hand.h"
#include "IGoOut.h"
#include <iostream>
#include <algorithm>
class Player {
public:
    Player();
    virtual void play() = 0;
	virtual bool playGame() = 0; // added might need to remove later

    void setCard(CardInterface* card);
    void setName(string *name);
    CardCollection* getHand();
    string getName();
    void setGoOutListener(IGoOut* iGoOut); // this must be made compulsory later
    void addToScore(int score);
	
	void playerGoOut(bool hasToGoOut); // set true when player has to go out // round should clear this while round ends
	void showDrawAndDiscardPile(); 
	void showHand();
	static void printCardsArrgmnt(vector<vector<CardInterface*>> cardsArgmnt);
	Hand* getPlayerHand();
	int getScore();
	
protected:
    Hand* hand;
    string* name;
    IGoOut* iGoOut;
    int score = 0; // initially all players have
    // the score of 0
	bool haveToGoOut = false;
};


#endif //FIVECROWNS_PLAYER_H
