//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_CARDINTERFACE_H
#define FIVECROWNS_CARDINTERFACE_H
#include <iostream>
#include <string>

using namespace std;

class CardInterface{
public:
    virtual string toString() = 0;
    string getFace(){
        if (face.empty()){
            throw "card doesn't have any face";
        }
        return this->face;
    }
    string getSuit(){

        if (suit.empty()){
            throw "card doesn't have any suit";
        }
        return this->suit;
    }
    void setFace(string face) {
        this->face = face;
    }
    void setSuit(string suit){
        this->suit = suit;
    }

    // Added consideration for Joker
    bool operator== (CardInterface* card){
            return this->getFace() == card->getFace() && this->getSuit() == card->getSuit();
    }
    // checks value of cards
    // doesn't consider suit in this regard
    bool operator<(CardInterface* card){
        return this->getValue() < card->getValue();
    }

    bool operator>(CardInterface* card){
        return this->getValue() > card->getValue();
    }

    int getValue(){
        // Note: only applicable for this game
        // Need to change so that can insert from deck

        // if joker return 50
        if (this->suit=="J") return 50;

        // if wildcard return 20
        if (this->face=="X") return 20;

        if (this->face == "K"){
            return 13;
        }
        if (this->face == "Q") return 12;
        if (this->face == "J") return 11;
        return stoi(this->face);
    }

    /**
     * Checks whether string value equals to the card.
     * for eg. passing 8D as string should match 8D card
     * @param card card in string format eg. 8D
     * @return true if string matches the card
     */

    bool match(string card){
        if (card.empty()) throw "card empty"; // throwing exception for now change it later
        return this->getFace() + this->getSuit() == card;
    }

	bool isSpecialCard() {
		if (this->suit == "J" || this->face == "X") {
			return true;
		}
		return false;
	}

//    virtual int getValue() = 0;
//    virtual string getFace() = 0;
//    virtual string getSuit() = 0;
//    virtual void setFace(string face) = 0;
//    virtual void setSuit(string suit) = 0;
//    virtual void setValue(int value) = 0;

private:
    string suit;
    string face;
};



#endif //FIVECROWNS_CARDINTERFACE_H

