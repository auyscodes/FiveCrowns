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


    vector<vector<CardInterface*>> genBooksAndRuns(){
        return genBooksAndRuns(this->collection);
    }
    vector<vector<CardInterface*>> genBooksAndRuns(vector<CardInterface*> cardsCol){
        sort(cardsCol.begin(), cardsCol.end(), compareCardsByValue);
        vector<vector<CardInterface*>> prevStack;
        vector<vector<CardInterface*>> nextStack = {cardsCol};
        vector<vector<CardInterface*>> output;
        while(!nextStack.empty()){
            prevStack = nextStack;
            output.insert(output.begin(), prevStack.begin(), prevStack.end());
            nextStack.clear();
            while(!prevStack.empty()){
                vector<CardInterface*> elem = *prevStack.begin();
                if (elem.size()!=3) {

                    for (unsigned int j=0;j<elem.size(); j++){
                        CardInterface* card = elem[j];
                        elem.erase(elem.begin() + j);
                        nextStack.insert(nextStack.begin(), elem);
                        elem.insert(elem.begin() + j, card);
                    }
                }
                prevStack.erase(prevStack.begin());
            }
        }
        int count = 0;
        while(!output.empty()){
            if (count == output.size()) break;
            CardCollection hand;
            hand.setCollectionVector(output[count]);
//            if (!checkRun(hand) && !checkBook(hand)) {
//                cout << "Not run or book" << endl;
//            }
            if (checkBook(hand)){
                cout << "Book " << hand.toString() << endl;
            }

            count++;
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

    static bool checkRun(CardCollection hand){
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
                    checkedSpecialCards.addFront(specialCards.popFront());
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

    // note: check book is returning wrong result
    static bool checkBook(CardCollection  hand){
        vector<CardCollection> normalAndSpecialCards = separateCards(hand);
        CardCollection normalCards = normalAndSpecialCards[0];
        CardCollection specialCards = normalAndSpecialCards[1];
        CardCollection* checkedSpecailCards = new CardCollection();
        if (normalCards.isEmpty()) return true;
        // no need to sort cards by value
        int size = normalCards.getSize();
        int count = 1;
        CardInterface* prevCard = normalCards.getFront();
        CardInterface* currCard;

        while(count<size){
            currCard = normalCards.getCardAt(count);
            if (prevCard->getValue() != currCard->getValue()){
                if (specialCards.isEmpty()) return false;
                checkedSpecailCards->addFront(specialCards.popFront());
            }
            prevCard = currCard;
            count++;
        }



        return true;
    }



    // remove this later
    void printOriginal(vector<CardInterface*> original){
        cout << "original : " ;
        for (int i=0;i<original.size();i++){
            cout << original[i]->toString() <<  " ";
        }
        cout << endl;
    }
    // remove this later
    void printTransformation(vector<vector<CardInterface* >> transformation){
        cout << "transformation : " ;
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

    // needs at least one elment or will generate error
    string serializer(vector<CardInterface*> cardCol){
        string serialized = cardCol.front()->toString();
        for (int i=1;i<cardCol.size();i++){
            serialized += " , " + cardCol[i]->toString();
        }
        return serialized;
    }

    // doesn't work now
    vector<CardCollection*> genPermutations(){
        // vector<vector<CardInterface*>> result =  generatePermutations();

        vector<CardInterface*> original = collection;

        vector<vector<CardInterface*>> result = genPermutationHelper(original);
        if (result.empty()) cout << "genPermutationHelper returned empty result" << endl;
        vector<CardCollection*> output;
        for (auto elem: result){
            CardCollection* cardCollection = new CardCollection();
            cardCollection->setCollectionVector(elem);
            output.push_back(cardCollection);
        }
        return output;
    }
private:
    vector <CardInterface* > collection;

    vector<vector<CardInterface*>> genPermutationHelper(vector<CardInterface*> original){

        if (original.size()==2) {
            return {{original[0], original[1]}, {original[1], original[0]}};
        }
        vector<vector<CardInterface*>> result;
        for (unsigned int i=0;i<original.size();i++){
            CardInterface* elem = *original.begin() + i;
            original.erase(original.begin() + i);
            vector<vector<CardInterface*>> transformed = transformation(genPermutationHelper(original), elem);
            result.insert(result.end(), transformed.begin(), transformed.end());
            original.insert(original.begin()+i, elem);
        }
        return result;
    }

    // result : ([ a,b], [c,d] ) and card e will be tranformed to : [e,a,b], [e,a,c]
    vector<vector<CardInterface*>> transformation(vector<vector<CardInterface*>> result, CardInterface* card){
        vector<vector<CardInterface*>> output;
        for (unsigned int resultIndex=0;resultIndex<result.size();resultIndex++){
            auto elem = result[resultIndex];
            elem.insert(elem.begin(), card);
            output.insert(output.begin(), elem);
        }
        return output;
    }

};


#endif //FIVECROWNS_CARDCOLLECTION_H

