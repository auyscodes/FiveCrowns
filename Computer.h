//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_COMPUTER_H
#define FIVECROWNS_COMPUTER_H


#include "Player.h"

class Computer: public Player {
public:
    void play();
	bool playGame();
private:
	// int cardIndexToRemoveCardAt(CardInterface* card, int& currScore, vector<vector<CardInterface*>>& currArrgnmnt); // helper function that helps finding from where to remove the card
	int getIndxToRmvCardAtHlpr( CardInterface* card, int& newScore, vector<vector<CardInterface*>>& newArrgnmnt, const int& currScore, CardCollection currHand);
	void printCardsArrgmnt(const vector<vector<CardInterface*>>& cardsArgmnt);
};


#endif //FIVECROWNS_COMPUTER_H
