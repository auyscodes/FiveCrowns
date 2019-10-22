//
// Created by nbhat on 9/15/2019.
//

#include "Computer.h"
#include "DiscardPile.h"
#include "DrawPile.h"
//void Computer::play() {
//
//	cout << "\n\nI am computer " << endl;
//	cout << "My name is " << *(this->name) << endl;
//	showDrawAndDiscardPile();
//	showHand();
//	CardCollection currHand = *(this->hand);
//	int currScore;
//	vector<vector<CardInterface*>> currArrgnmnt;
//	currHand.minScoreAndBranch(currScore, currArrgnmnt);
//	if (currScore == 0) {
//		// needs to go out here
//	}
//
//	int newScore;
//	vector<vector<CardInterface*>> newArrgnmnt;
//	//CardInterface* disCard = DiscardPile::getInstance()->getFront(); // gets card from discardPile doesn't change the discard pile card
//	int cardIndex = getIndxToRmvCardAtHlpr(DiscardPile::getInstance()->getFront(), newScore, newArrgnmnt, currScore, currHand);
//
//	
//	if (cardIndex != -1) {
//		
//		hand->addCardAt(cardIndex, DiscardPile::getInstance()->popFront()); // removes the discard pile card permanently and adds it to players hand
//		
//		DiscardPile::getInstance()->addFront(hand->popCardAt(cardIndex + 1)); // // removes card permanently from hand and adds it to the discard pile
//		// notice that cardIndex above increases by 1
//
//		cout << "The computer chose to pick up from the discard pile because replacing a card with " << hand->getCardAt(cardIndex)->toString() << " card " << " helped make ";
//		printCardsArrgmnt(newArrgnmnt);
//		cout << endl;
//
//		cout << "It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(cardIndex)->toString() << " card reduced the minimum score from "
//			<< currScore << " to " << newScore << endl;
//
//			 
//	}
//	else {
//		
//		cout << "The computer chose to pick from drawpile because the card present in discard pile did not reduce the minimum score " << endl;
//
//		CardInterface* drawCard = DrawPile::getInstance()->popFront(); // removes the card from drawpile permanently
//		int index = getIndxToRmvCardAtHlpr(drawCard, newScore, newArrgnmnt, currScore, currHand);
//		
//		
//		
//		
//		if (index == -1) {
//			DiscardPile::getInstance()->addFront(drawCard);
//
//			cout << "The computer chose to throw the card picked up from drawpile because the card did not reduce the minimum score " << endl;
//
//		}
//		else {
//			cout << " index : " << index << endl;
//			// condition so that computer doesn't throw joker or wildcard
//
//			cout << " is it a special card : " << hand->getCardAt(index)->toString() << " , " << hand->getCardAt(index)->isSpecialCard() << endl;
//			if (hand->getCardAt(index)->isSpecialCard()) {
//				cout << " haha hehe " << endl;
//			}
//
//
//			if (!hand->getCardAt(index)->isSpecialCard()) {
//				hand->addCardAt(index, drawCard); // adds card permanently to hand
//				DiscardPile::getInstance()->addFront(hand->popCardAt(index + 1)); // removes card permanently from hand
//
//				cout << "Replacing a card in computer's hand with " << hand->getCardAt(index)->toString() << " card " << " helped make ";
//				printCardsArrgmnt(newArrgnmnt);
//				cout << endl;
//				cout << " It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(index)->toString() << " card reduced the minimum score from "
//					<< currScore << " to " << newScore << endl;
//			} else
//			{
//				DiscardPile::getInstance()->addFront(drawCard);
//				cout << "The computer chose to throw card picked from discard pile because it decided to keep special card " << endl;
//			}
//			
//			
//		}
//	}
//}

bool Computer::playGame() {
	cout << "\n\nI am computer " << endl;
	cout << "My name is " << *(this->name) << endl;
	showDrawAndDiscardPile();
	showHand();
	CardCollection currHand = *(this->hand);
	int currScore;
	vector<vector<CardInterface*>> currArrgnmnt;
	currHand.minScoreAndBranch(currScore, currArrgnmnt);
	if (currScore == 0) {
		return true;
	}

	int newScore;
	vector<vector<CardInterface*>> newArrgnmnt;
	//CardInterface* disCard = DiscardPile::getInstance()->getFront(); // gets card from discardPile doesn't change the discard pile card
	int cardIndex = getIndxToRmvCardAtHlpr(DiscardPile::getInstance()->getFront(), newScore, newArrgnmnt, currScore, currHand);


	if (cardIndex != -1) {

		hand->addCardAt(cardIndex, DiscardPile::getInstance()->popFront()); // removes the discard pile card permanently and adds it to players hand

		DiscardPile::getInstance()->addFront(hand->popCardAt(cardIndex + 1)); // // removes card permanently from hand and adds it to the discard pile
		// notice that cardIndex above increases by 1

		cout << "The computer chose to pick up from the discard pile because replacing a card with " << hand->getCardAt(cardIndex)->toString() << " card " << " helped make ";
		printCardsArrgmnt(newArrgnmnt);
		cout << endl;

		cout << "It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(cardIndex)->toString() << " card reduced the minimum score from "
			<< currScore << " to " << newScore << endl;

		if (newScore == 0) return true; // goes out if score is equals to 0

	}
	else {

		cout << "The computer chose to pick from drawpile because the card present in discard pile did not reduce the minimum score " << endl;

		CardInterface* drawCard = DrawPile::getInstance()->popFront(); // removes the card from drawpile permanently
		int index = getIndxToRmvCardAtHlpr(drawCard, newScore, newArrgnmnt, currScore, currHand);




		if (index == -1) {
			DiscardPile::getInstance()->addFront(drawCard);

			cout << "The computer chose to throw the card picked up from drawpile because the card did not reduce the minimum score " << endl;

			
			return false;
		}
		else {
			

			// condition so that computer doesn't throw joker or wildcard 
			if (!hand->getCardAt(index)->isSpecialCard()) {
				hand->addCardAt(index, drawCard); // adds card permanently to hand
				DiscardPile::getInstance()->addFront(hand->popCardAt(index + 1)); // removes card permanently from hand

				cout << "Replacing a card in computer's hand with " << hand->getCardAt(index)->toString() << " card " << " helped make ";
				printCardsArrgmnt(newArrgnmnt);
				cout << endl;
				cout << " It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(index)->toString() << " card reduced the minimum score from "
					<< currScore << " to " << newScore << endl;
				if (newScore == 0) return true;
			}
			else
			{
				DiscardPile::getInstance()->addFront(drawCard);
				cout << "The computer chose to throw card picked from discard pile because it decided to keep special card " << endl;

				return false;
			}


		}
	}
	return false;
}


int Computer::getIndxToRmvCardAtHlpr( CardInterface* card, int& newScore, vector<vector<CardInterface*>>& newArrgnmnt, const int& currScore, CardCollection currHand) {
	

	
	
	
	newScore = currScore;
	int cardIndex = -1;
	for (int i = 0; i < currHand.getSize(); i++) {
		vector<vector<CardInterface*>> arrgnmnt;
		int score;
		CardInterface* handCard = currHand.popCardAt(i); // removes card permanently and returns it
		
		currHand.addCardAt(i, card);
		currHand.minScoreAndBranch(score, arrgnmnt);
		
		if (score < newScore) {
			newScore = score;
			newArrgnmnt = arrgnmnt;
			cardIndex = i;
		}
		currHand.popCardAt(i);
		currHand.addCardAt(i, handCard);

	}
	return cardIndex;
}
bool Computer::canGoOutWithoutPicking(Hand _hand, int&score, vector<vector<CardInterface*>>& arrgnmnt) {
	CardCollection& currHand = _hand;
	int currScore;
	vector<vector<CardInterface*>> currArrgnmnt;
	currHand.minScoreAndBranch(currScore, currArrgnmnt);
	score = currScore;
	arrgnmnt = currArrgnmnt;
	if (currScore == 0) {
		return true;
	}
	return false;
}

bool Computer::pickCardFromDiscardPile(Hand hand, int hand_score , int& index, vector<vector<CardInterface*>>& arrgnmnt, int&score) {
	index = -1;
	int newScore;
	vector<vector<CardInterface*>> newArrgnmnt;
	//CardInterface* disCard = DiscardPile::getInstance()->getFront(); // gets card from discardPile doesn't change the discard pile card
	int cardIndex = getIndxToRmvCardAtHlpr(DiscardPile::getInstance()->getFront(), newScore, newArrgnmnt, hand_score, hand);
	if (cardIndex >= 0) {
		index = cardIndex;
		arrgnmnt = newArrgnmnt;
		score = newScore;
		return true;
	}
	return false;
}


void Computer::helpPick(Hand _hand) { // change hardcoded mode later
		int currScore; // needed for deciding to pick from discard pile
		vector<vector<CardInterface*>> currArrgnmnt;
		bool goOutWithoutPicking = canGoOutWithoutPicking(_hand, currScore, currArrgnmnt);
		if (goOutWithoutPicking) {
			cout << "I recommend you to go out without picking any card" << endl;
			cout << "Current score is : " << currScore << endl;;
			cout << "Current arrangement of cards is : ";
			printCardsArrgmnt(currArrgnmnt);
			cout << endl;
			return;
		}
		int index;
		vector<vector<CardInterface*>> arrgnmnt;
		int score;
		bool keepDisCard = pickCardFromDiscardPile(_hand, currScore, index, arrgnmnt, score);
		if (keepDisCard) {
			cout << "I recommed you to pick card from discard pile " << endl;
			cout << "I recommend you to pick up from the discard pile because replacing a card with " << DiscardPile::getInstance()->getFront()->toString() << " card " << " helps make ";
			printCardsArrgmnt(arrgnmnt);
			cout << endl;

			cout << "Replacing " << _hand.getCardAt(index)->toString() << " with " << DiscardPile::getInstance()->getFront()->toString() << " card reduced the minimum score from "
				<< currScore << " to " << score << endl;
			return;
		}
		cout << "I recommend you to pick card from drawPile " << endl;
		return;
		

		
	
}

void Computer::helpThrow(Hand _hand, CardInterface* card) {
	
	// all this to curr score
	int currScore; // needed for deciding to pick from discard pile
	vector<vector<CardInterface*>> currArrgnmnt;
	_hand.minScoreAndBranch(currScore, currArrgnmnt);
	if (currScore == 0) {
		cout << "I recommend you to throw " << card->toString() << " card because all the cards in your hand can be arragned to ";
		printCardsArrgmnt(currArrgnmnt);
		cout << " to get minimum score of " << currScore;
		return;
	}
	// end of all this

	int new_score;
	vector<vector<CardInterface*>> newArrgnmnt;
	int index = getIndxToRmvCardAtHlpr(card, new_score, newArrgnmnt, currScore, _hand);
	if (index == -1) {
		cout << "I recommend you to throw card " << card->toString() << " because replacing any other card with the card will increase minimum score " << endl;
		return;
	}
	
	cout << "I recommed you to throw " << _hand.getCardAt(index)->toString() << " card because replacing that card with " << card->toString()
		<< " card reduces minimum score from " << currScore << " to " << new_score << endl;

	cout << "Your new cards arrangement will be ";
	printCardsArrgmnt(newArrgnmnt);
	cout << endl;
	cout << "Your old cards arrangement was ";
	printCardsArrgmnt(currArrgnmnt);
	cout << endl;

}

// note: this function is repeating in both human and computer change it later
void Computer::printCardsArrgmnt(const vector<vector<CardInterface*>>& cardsArgmnt)
{
	cout << " [ ";
	for (auto argmnt : cardsArgmnt) {
		cout << " [ ";
		for (auto elem : argmnt) {
			cout << elem->toString() << " ";
		}
		cout << " ] ";
	}
	cout << " ] ";
}