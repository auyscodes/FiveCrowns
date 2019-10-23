//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_COMPUTER_H
#define FIVECROWNS_COMPUTER_H


#include "Player.h"

class Computer: public Player {
public:
    
	bool playGame();
	static void helpPick(Hand _hand);
	static void helpThrow(Hand _hand, CardInterface* _card);
	static bool canGoOutWithoutPicking(Hand hand, int&score, vector<vector<CardInterface*>>& arrgnmnt);

	// not should provide hand socre to this helper function
	static bool pickCardFromDiscardPile(Hand hand, int hand_score , int&index, vector<vector<CardInterface*>>& arrgnmnt, int&score);
	
private:
	// int cardIndexToRemoveCardAt(CardInterface* card, int& currScore, vector<vector<CardInterface*>>& currArrgnmnt); // helper function that helps finding from where to remove the card
	static int getIndxToRmvCardAtHlpr( CardInterface* card, int& newScore, vector<vector<CardInterface*>>& newArrgnmnt, const int& currScore, CardCollection currHand);
	static void printCardsArrgmnt(const vector<vector<CardInterface*>>& cardsArgmnt);
	

	
};


#endif //FIVECROWNS_COMPUTER_H

