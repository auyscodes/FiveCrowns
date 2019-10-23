//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_PLAYER_H
#define FIVECROWNS_PLAYER_H


#include "Hand.h"

#include "ISave.cpp"
#include <iostream>
#include <algorithm>
class Player {
public:
    Player();
	virtual bool playGame() = 0; 
    void setCard(CardInterface* card);
    void setName(string *name);
	void setSaveGameCallback(Save* iSave);
	void setPlayerHand(Hand* hand);
	void setScore(int score); 
	void addToScore(int score);
    CardCollection* getHand();
    string getName();
	void playerGoOut(bool hasToGoOut); // set true when player has to go out // cleared at end of each round
	void showDrawAndDiscardPile(); 
	void showHand();
	static void printCardsArrgmnt(vector<vector<CardInterface*>> cardsArgmnt);
	Hand* getPlayerHand();
	int getScore();
	~Player();
protected:
    Hand* hand;
    string* name;
	Save* iSave;
    int score = 0; // initially all players have
    // the score of 0
	bool haveToGoOut = false; // intially all players do not have to go out
};


#endif //FIVECROWNS_PLAYER_H
