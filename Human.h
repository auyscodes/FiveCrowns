//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_HUMAN_H
#define FIVECROWNS_HUMAN_H


#include "Player.h"

class Human: public Player {
public:
    // void play();
	bool playGame();
private:
	// void printCardsArrgmnt(vector<vector<CardInterface*>> cardsArgmnt);
    // void askToChooseCardFromDrawPileOrDiscardPile();

	bool moveHelper(); // added might need to remove if doesn't work out

	void throwCard();
	void throwCardAtIndex();
	bool goOut();
};


#endif //FIVECROWNS_HUMAN_H
