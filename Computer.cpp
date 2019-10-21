//
// Created by nbhat on 9/15/2019.
//

#include "Computer.h"
#include "DiscardPile.h"
#include "DrawPile.h"
void Computer::play() {

	cout << "\n\nI am computer " << endl;
	cout << "My name is " << *(this->name) << endl;
	showDrawAndDiscardPile();
	showHand();
	CardCollection currHand = *(this->hand);
	int currScore;
	vector<vector<CardInterface*>> currArrgnmnt;
	currHand.minScoreAndBranch(currScore, currArrgnmnt);
	if (currScore == 0) {
		// needs to go out here
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

			 
	}
	else {
		
		cout << "The computer chose to pick from drawpile because the card present in discard pile did not reduce the minimum score " << endl;

		CardInterface* drawCard = DrawPile::getInstance()->popFront(); // removes the card from drawpile permanently
		int index = getIndxToRmvCardAtHlpr(drawCard, newScore, newArrgnmnt, currScore, currHand);
		
		
		
		
		if (index == -1) {
			DiscardPile::getInstance()->addFront(drawCard);

			cout << "The computer chose to throw the card picked up from drawpile because the card did not reduce the minimum score " << endl;

		}
		else {
			cout << " index : " << index << endl;
			// condition so that computer doesn't throw joker or wildcard

			cout << " is it a special card : " << hand->getCardAt(index)->toString() << " , " << hand->getCardAt(index)->isSpecialCard() << endl;
			if (hand->getCardAt(index)->isSpecialCard()) {
				cout << " haha hehe " << endl;
			}


			if (!hand->getCardAt(index)->isSpecialCard()) {
				hand->addCardAt(index, drawCard); // adds card permanently to hand
				DiscardPile::getInstance()->addFront(hand->popCardAt(index + 1)); // removes card permanently from hand

				cout << "Replacing a card in computer's hand with " << hand->getCardAt(index)->toString() << " card " << " helped make ";
				printCardsArrgmnt(newArrgnmnt);
				cout << endl;
				cout << " It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(index)->toString() << " card reduced the minimum score from "
					<< currScore << " to " << newScore << endl;
			} else
			{
				DiscardPile::getInstance()->addFront(drawCard);
				cout << "The computer chose to throw card picked from discard pile because it decided to keep special card " << endl;
			}
			
			
		}
	}
}

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
			cout << " index : " << index << endl;
			// condition so that computer doesn't throw joker or wildcard

			cout << " is it a special card : " << hand->getCardAt(index)->toString() << hand->getCardAt(index)->isSpecialCard() << endl;
			if (hand->getCardAt(index)->isSpecialCard()) {
				cout << " haha hehe " << endl;
			}


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
	

	// CardCollection currHand = *(this->hand);
	
	
	newScore = currScore;
	int cardIndex = -1;
	for (int i = 0; i < hand->getSize(); i++) {
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