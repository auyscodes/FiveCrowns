//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_CARDCOLLECTION_H
#define FIVECROWNS_CARDCOLLECTION_H

#include <random>
#include <vector>
#include "CardInterface.h"
#include <algorithm>
#include <iostream>
#include "CompareCardByValue.h"
#include <map>
class CardCollection{

public:

    void addFront(CardInterface* card){
        this->collection.insert(collection.begin(), card);
    }

    void addBack(CardInterface* card) {
        this->collection.insert(collection.end(), card);
    }

    CardInterface* getFront(){
        return *collection.begin();
    }

    CardInterface* getBack(){
        return *(collection.begin() + collection.size());
    }

    CardInterface* popFront(){
        CardInterface* card = *(collection.begin());
        collection.erase(collection.begin());
        return card;
    }
    CardInterface * popBack(){
        CardInterface * card = *(collection.begin() + collection.size());
        collection.erase(collection.begin()+ collection.size());
        return card;
    }

    bool isEmpty(){
        return collection.empty() || false;
    }
    int getSize(){
        return collection.size();
    }
    CardInterface*  getCardAt(int position){
        return collection[position];
    }

    // removes a card permanently and also returns that card
    CardInterface* popCardAt(int position){
        CardInterface* card = *(collection.begin() + position);
        collection.erase(collection.begin() + position);
        return card;
    }


    // Function uses overloaded operator (equals to)= need to check if (equals to)= handles wild card and joker or not
    CardInterface* popCard(CardInterface * card){
        for (int i=0;i<collection.size();i++){
            if (collection[i] == card){
                CardInterface * temp = collection[i];
                collection.erase(collection.begin() + i);
                return temp;
            }
        }
    }

    void shuffle(){
        std::shuffle(collection.begin(), collection.end(), std::mt19937(std::random_device()()));
    }



    void collect(CardCollection* cardCollection){
        int size = cardCollection->getSize(); // !!! important to put cardcollection size in a variable otherwise will get error
        for (int i=0;i<size;i++){
            collection.push_back(cardCollection->popFront());
        }
    }
    void transformCards(string face, string wildcard){
        // since Joker is of suit J and has 1 2 3 . Conflicts with regular 3 card. So have to check. Can make Joker start at 0 1 and 2 for easy purposes
        for (auto card: this->collection){
            if (card->getFace() == face && card->getSuit()!="J") card->setFace(wildcard);
        }
    }

    vector<CardCollection*> separateNormalCardsFromOthers(){
        CardCollection* normalCards = new CardCollection();
        CardCollection* specialCards = new CardCollection();
        for (CardInterface* card : collection){
            if (card->getSuit()=="J" || card->getFace()=="X"){
                specialCards->addFront(card);
                continue;
            }
            normalCards->addFront(card);

        }
        return {normalCards, specialCards};
    }

	
	
    string toString(){
        string output;
        for (auto card: collection){
            output += card->toString() + " ";
            // cout << card->toString() << " ";
        }
        // cout << endl;
        // cout << output;
        return output;
    }

    bool sameSuit(){
        if (collection.empty()) cout << "collection empty xa " << endl;
        string suitOfFirstCard = collection.front()->getSuit(); //this is throwing vector iterator out of range error
        for (int i=1;i<collection.size();i++){
            if (collection[i]->getSuit() != suitOfFirstCard) return false;
        }
        return true;
    }

    void sortCardsByValue(){
        std::sort(collection.begin(), collection.end(), compareCardsByValue);
    }


    static bool compareCardsByValue(CardInterface* card1, CardInterface* card2){
        return card1->getValue() < card2->getValue();
    }

    void setCollectionVector(vector<CardInterface*> col){
        this->collection  = col;
    }

	// change from here

	

	
    

    bool checkBook(vector<CardInterface*> cards){
        CardCollection hand;
        hand.setCollectionVector(cards);
        return checkBook(hand);
    }
    bool checkRun(vector<CardInterface*> cards){
        CardCollection hand;
        hand.setCollectionVector(cards);
        return checkRun(hand);
    }

    //vector<CardInterface*> removeCards(vector<CardInterface*>& hand, vector<CardInterface*> curr){
    //    // sorting cards by value
    //    sort(curr.begin(), curr.end(), compareCardsByValue);

    //     int handPointer = hand.size() - 1;
    //     int currPointer = curr.size() - 1;
    //    vector<CardInterface*> removedCards;

		

    //    while(handPointer >= 0 && currPointer >= 0 ){
    //        if (hand.empty() || curr.empty()) break;
    //        if (hand[handPointer] == curr[currPointer]) {
    //            removedCards.push_back(hand[handPointer]);
    //            hand.erase(hand.begin() + handPointer);
    //            currPointer--;
    //        }
    //        handPointer--;
    //    }
    //    return removedCards;

    //}
	vector<CardInterface*> removeCards(vector<CardInterface*>& hand, vector<CardInterface*> curr) {
		vector<CardInterface*> output;
		bool currContains = false;
		
		for (int i = hand.size()-1; i >= 0; i--) {
			CardInterface* handCard = hand[i];

			for (int j = curr.size()-1; j >=0 ; j--) {
				if (handCard == curr[j]) currContains = true;
			}
			if (currContains) {
				output.push_back(handCard);
				hand.erase(hand.begin() + i);
				
				currContains = false;
			}


		}
		return output;
	}
	

    void addCards(vector<CardInterface*>&hand, vector<CardInterface*> curr){
        hand.insert(hand.end(), curr.begin(), curr.end());
        sort(hand.begin(), hand.end(), compareCardsByValue);
    }


	vector<vector<CardInterface*>> getBestPossibleBooksAndRuns() {

		vector<vector<CardInterface*>> listOfBooksAndRuns;
		vector<CardInterface*> hand = this->collection;
		// don't remove sort here
		sort(hand.begin(), hand.end(), compareCardsByValue);


		vector<vector<CardInterface*>> branch;
		vector<vector<CardInterface*>> minBranch;
		int minScore = INT_MAX;
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		genBestHelper(hand, branch, minBranch, minScore);
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return minBranch;


	}



	void genBestHelper(vector<CardInterface*>& hand, vector<vector<CardInterface*>>& branch, vector<vector<CardInterface*>>& minBranch, int& minScore) {
		/*cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;*/
		vector<vector<CardInterface*>>  listOfBooksAndRuns = genBooksAndRuns(hand);
		/*cout << "hand ";
		printOriginal(hand);
		cout << endl;
		cout << " branch ";
		printTransformation(branch);
		cout << endl;
		cout << "=====================================================" << endl;*/
		/*cout << " min Branch ";
		printTransformation(minBranch);
		cout << endl;
		cout << " listOfBooksAndRuns ";
		printTransformation(listOfBooksAndRuns);
		cout << endl;
		cout << "minScore ";
		cout << minScore << endl;
		
		cout << " check book and run " << checkBook(hand) << checkRun(hand ) << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;*/
		// previous checkBook and checkRun
		if (listOfBooksAndRuns.empty()) { // check book and check run do not handle combo of books and runs so is gii
			int score = countScore(hand);
			if (score <= minScore) {
				minScore = score;
				minBranch = branch;
				if (!hand.empty()) {
					minBranch.push_back(hand);

					
				}
				
				cout << endl;
				cout << "minScore : " << minScore << endl;
				cout << "socre : " << score << endl;
				cout << "minBranch : ";
				printTransformation(minBranch);

			}
			
		}
		else {
			for (unsigned int i = 0; i < listOfBooksAndRuns.size(); i++) {

				vector<CardInterface*> curr = listOfBooksAndRuns[i];





				/*cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
				cout << "hand before removing cards : ";
				printOriginal(hand);
				cout << "curr : ";
				printOriginal(curr);
				cout << endl;*/



				vector<CardInterface*> removedCards = removeCards(hand, curr);



				//cout << "removed cards : ";
				//printOriginal(removedCards);
				//cout << " hand after removing cards : ";
				//printOriginal(hand);


				if (removedCards.size() == 1) {


					cout << "hand";
					printOriginal(hand);
					cout << "list of books and runs ";
					printTransformation(listOfBooksAndRuns);
					
					cout << "current listofBooksAndRuns : ";
					printOriginal(curr);

					cout << "current index : " << i << endl;
					cout << " here here " << endl;
					
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					
				}
				// cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5" << endl;
				if (!removedCards.empty()) {
					branch.push_back(removedCards);
				}
				

				genBestHelper(hand, branch, minBranch, minScore);
				
				
				if (!removedCards.empty()) {
					branch.pop_back();
				}
				
				/*cout << "removed cards : ";
				printOriginal(removedCards);
				cout << "hand before adding removed cards  : ";
				printOriginal(hand);
				*/
				
				addCards(hand, removedCards);


				/*cout << " hand after adding removed cards : ";
				printOriginal(hand);*/
			}
		}
	}
	int countScore(vector<CardInterface*> hand) {
		int sum = 0;
		for (auto card : hand) {
			sum += card->getValue();
		}
		return sum;
	}

	// just for checking outside remove it later
    vector<vector<CardInterface*>> genBooksAndRuns(){

        return genBooksAndRuns(this->collection);
    }



	vector<vector<CardInterface*>> genBooksAndRuns(vector<CardInterface*> cardsCol) {
		vector<vector<CardInterface*>> output;
		if (cardsCol.size() < 3) return output;

		vector<vector<CardInterface*>> books = genBooks(cardsCol);
		vector<vector<CardInterface*>> run = genRuns(cardsCol);
		
		
		output.insert(output.begin(), books.begin(), books.end());
		output.insert(output.begin(), run.begin(), run.end());
		return output;
    	
		
	}

	vector<vector<CardInterface*>> genBooks(vector<CardInterface*> cardsCol)
    {
		vector<vector<CardInterface*>> separateCards = separateNormalAndSpecialCards(cardsCol);
		vector<CardInterface*>& normalCards = separateCards[0];
		vector<CardInterface*>& specialCards = separateCards[1];

		vector<vector<CardInterface*>> dividedCards = divideCards(normalCards);
		/*for (int i=0;i<dividedCards.size();i++)
		{
			vector<CardInterface*>& elem = dividedCards[i];
			for (auto specialCard : specialCards) {
				elem.push_back(specialCard);
			}
		}*/
		vector<vector<CardInterface*>> dividedCardsWSpCards = addSpecialCards(dividedCards, specialCards);

		vector<vector<CardInterface*>> output;
		for (auto elem : dividedCardsWSpCards) {
			if (checkBook(elem)) output.push_back(elem);
		}
		return output;
    	
    	
    }

	// just exposing it for now
	vector<vector<CardInterface*>> genRuns()
    {
		return genRuns(this->collection);
    }
	
	vector<vector<CardInterface*>> genRuns(vector<CardInterface*> cardsCol)
    {
    	
		
		
		vector<vector<CardInterface*>> separateCards = separateNormalAndSpecialCards(cardsCol);
		vector<CardInterface*> normalCards = separateCards[0];
		vector<CardInterface*> specialCards = separateCards[1];

		vector<vector<CardInterface*>> divideSuits = separateSuits(normalCards);


	
		// suru ma divide garne ani matra joker add garne
    	/*for (int i=0;i<divideSuits.size();i++)
    	{
			vector<CardInterface*>& suit = divideSuits[i];
			if (suit.empty()) continue;
    		for (int j=0;j<specialCards.size(); j++)
    		{
				CardInterface* elem = specialCards[j];
				suit.push_back(elem);
    		}
    		
    	}*/
		vector<vector<CardInterface*>> output;

		for (auto suitOfCards : divideSuits) {
			vector < vector<CardInterface*>> dividedSuitOfCards = divideCards(suitOfCards);
			vector<vector<CardInterface*>> dividedSuitsWithSpCards = addSpecialCards(dividedSuitOfCards, specialCards);
			for (auto elem : dividedSuitsWithSpCards) {
				if (checkRun(elem)) {
					output.push_back(elem);
				}
			}
		}


    	/*for (auto suitOfCards: divideSuits)
    	{
			vector<vector<CardInterface*>> dividedSuitOfCards = divideCards(suitOfCards);
			for (auto elem: dividedSuitOfCards)
			{
				if (checkRun(elem))
				{
					output.push_back(elem);
				}
			}
    	}*/


		return output;
    }

	// only for testing
	vector<vector<CardInterface*>> addSpecialCards() {
		vector<vector<CardInterface*>> normalAndSpecialCards = separateNormalAndSpecialCards(this->collection);
		vector<vector<CardInterface*>> dividedCards = divideCards(normalAndSpecialCards[0]);
		return addSpecialCards(dividedCards, normalAndSpecialCards[1]);
	}


	// Not your simple addition
	// to make so that keeps cards without special cards as well
	vector<vector<CardInterface*>> addSpecialCards(vector<vector<CardInterface*>> cardsCol , vector<CardInterface*> specialCards) {

		
		vector<vector<CardInterface*>> spCardsList;
		for (int i = 0; i < specialCards.size(); i++) {
			vector<CardInterface*> spCards;
			for (int j = 0; j <=i; j++) {
				spCards.push_back(specialCards[j]);
			}
			spCardsList.push_back(spCards);
		}
		
		vector<vector<CardInterface*>> output;
		for (int i = 0; i < cardsCol.size(); i++) {
			
			for (int j = 0; j < spCardsList.size(); j++) {
				vector<CardInterface*> elem = cardsCol[i];
				vector<CardInterface*> spCards = spCardsList[j];
				elem.insert(elem.end(), spCards.begin(), spCards.end());
				if (elem.size() >= 3) {
					output.push_back(elem);
				}
			}
			// also need to add cardsCol where elem size is greater than 3
			if (cardsCol[i].size() >= 3) output.push_back(cardsCol[i]);

		}
		
		return output;
	}

	// cards passed here should not be special cards
	vector<vector<CardInterface*>> separateSuits(vector<CardInterface*> cardsCol)
    {
		
		
		vector<CardInterface*> hearts;
		vector<CardInterface*> diamonds;
		vector<CardInterface*> clubs;
		vector<CardInterface*> tridents;
		vector<CardInterface*> spades;

    	for (auto card: cardsCol)
    	{
			if (card->getSuit() == "H") hearts.push_back(card);
			if (card->getSuit() == "T") tridents.push_back(card);
			if (card->getSuit() == "C") clubs.push_back(card);
			if (card->getSuit() == "S") spades.push_back(card);
			if (card->getSuit() == "D") diamonds.push_back(card);
    		
    	}
		
		
		return { hearts, diamonds, clubs, spades, tridents };
    }


	// duplicate function
	
	vector<vector<CardInterface*>> separateNormalAndSpecialCards(vector<CardInterface*> cardsCol)
    {
		
		
		vector<CardInterface*> normalCards;
		vector<CardInterface*> specialCards;
		for (unsigned int i = 0; i < cardsCol.size(); i++) {
			CardInterface* card = cardsCol[i];
			if (card->getSuit() == "J" || card->getFace() == "X") {
				specialCards.push_back(card);
				continue;
			}
			normalCards.push_back(card);

		}
		
		return { normalCards, specialCards };
    }
	
	vector<vector<CardInterface*>> divideCards() {
		return divideCards(this->collection);
	}

	//vector<vector<CardInterface*>> divideCards(vector<CardInterface*> cardsCol)
 //   {
	//	
	//	sort(cardsCol.begin(), cardsCol.end(), compareCardsByValue);
	//	
	//	vector<vector<CardInterface*>> output;

 //   	// for now
	//	if (cardsCol.empty()) return output;
 //   	
	//	for (int i = 0; i < cardsCol.size() - 2; i++)
	//	{
	//		for (int j = i + 2; j < cardsCol.size(); j++)
	//		{
	//			vector<CardInterface*> result;
	//			// change this for loop later to more nicer code to copy
	//			for (int k = i; k <= j; k++)
	//			{
	//				result.push_back(cardsCol[k]);
	//			}
	//			output.push_back(result);
	//		}
	//	}
	//	
	//	return output;
 //   	
 //   }
	vector<vector<CardInterface*>> divideCards(vector<CardInterface*> cardsCol) {
		sort(cardsCol.begin(), cardsCol.end(), compareCardsByValue);
		
		vector<vector<CardInterface*>> output;

    	// for now
		if (cardsCol.empty()) return output;
    	
		for (int i = 0; i < cardsCol.size(); i++)
		{
			for (int j = i; j < cardsCol.size(); j++)
			{
				vector<CardInterface*> result;
				// change this for loop later to more nicer code to copy
				for (int k = i; k <= j; k++)
				{
					result.push_back(cardsCol[k]);
				}
				output.push_back(result);
			}
		}
		
		return output;
	}

	
   
    // Note: this doesn't modify the passed hand
    static vector<CardCollection> separateCards(CardCollection collection1){
        CardCollection normalCards;
        CardCollection specialCards;
        for (unsigned int i=0;i<collection1.getSize();i++){
            CardInterface* card = collection1.getCardAt(i);
//        for (CardInterface* card : collection1){
            if (card->getSuit()=="J" || card->getFace()=="X"){
                specialCards.addFront(card);
                continue;
            }
            normalCards.addFront(card);

        }
        return {normalCards, specialCards};
    }

	// handles only same suit and joker
	// does not handle combo of suit and joker
    static bool checkRun(CardCollection hand){
		
        if (hand.getSize()<3) return false;
		
        vector<CardCollection> normalAndSpecialCardsOfHands = separateCards(hand);

        CardCollection normalCards = normalAndSpecialCardsOfHands[0];
        CardCollection specialCards = normalAndSpecialCardsOfHands[1];

		
        if (normalCards.isEmpty()) return true;

        CardCollection checkedSpecialCards;

        normalCards.sortCardsByValue();

        if (normalCards.sameSuit()){
            int size = normalCards.getSize();
            CardInterface* prevCard = normalCards.getFront();
            CardInterface* currCard;
            int count = 1;
            while(count< size){
                currCard = normalCards.getCardAt(count);
                if (prevCard->getValue() != currCard->getValue() - 1){
                    if (specialCards.isEmpty()) return false;
                    if (prevCard->getValue() != currCard->getValue()-2) {
                        return false;
                    }
                    else{
                        checkedSpecialCards.addFront(specialCards.popFront());
                    }

                }
                prevCard = currCard;
                count++;
            }
            return true;
        }
        return false;
    }
    // assumption hand always has cards greater than 3
    // if special cards are not present then hand has joker or wildcards only
	// handles only single sequence of books and runs
	// doesn't handle 33J44J conditions
    static bool checkBook(CardCollection  hand){

        if (hand.getSize()<3) return false;

        vector<CardCollection> normalAndSpecialCards = separateCards(hand);
        CardCollection normalCards = normalAndSpecialCards[0];
        CardCollection specialCards = normalAndSpecialCards[1];

        if (normalCards.isEmpty()) return true;

        // no need to sort cards by value
        int size = normalCards.getSize();
        int count = 1;
        CardInterface* prevCard = normalCards.getFront();
        CardInterface* currCard;

        while(count<size){
            currCard = normalCards.getCardAt(count);
            if (prevCard->getValue() != currCard->getValue()){
                return false;
            }
            prevCard = currCard;
            count++;
        }


        return true;
    }


	


    // remove this later
    void printOriginal(vector<CardInterface*> original){
        // cout << "original : " ;
        for (int i=0;i<original.size();i++){
            cout << original[i]->toString() <<  " ";
        }
        cout << endl;
    }
    // remove this later
    void printTransformation(vector<vector<CardInterface* >> transformation){
        // cout << "transformation : " ;
        cout << "[ ";
        for (auto elem: transformation){
            cout << "[ ";
            for (auto e: elem){
                cout << e->toString() << " ";
            }
            cout << " ] ";
        }
        cout << " ] " << endl;
        cout << endl;
    }


   
private:
    vector <CardInterface* > collection;

};


#endif //FIVECROWNS_CARDCOLLECTION_H

