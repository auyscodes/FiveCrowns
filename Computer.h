//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_COMPUTER_H
#define FIVECROWNS_COMPUTER_H


#include "Player.h"

class Computer: public Player {
public:
    // void play();
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

//if (cardIndex != -1) {
//
//	hand->addCardAt(cardIndex, DiscardPile::getInstance()->popFront()); // removes the discard pile card permanently and adds it to players hand
//
//	DiscardPile::getInstance()->addFront(hand->popCardAt(cardIndex + 1)); // // removes card permanently from hand and adds it to the discard pile
//	// notice that cardIndex above increases by 1
//
//	cout << "The computer chose to pick up from the discard pile because replacing a card with " << hand->getCardAt(cardIndex)->toString() << " card " << " helped make ";
//	printCardsArrgmnt(newArrgnmnt);
//	cout << endl;
//
//	cout << "It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(cardIndex)->toString() << " card reduced the minimum score from "
//		<< currScore << " to " << newScore << endl;
//
//
//}
//else {
//}
