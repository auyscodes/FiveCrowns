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
    bool operator== (CardInterface* card){
        return this->getFace() == card->getFace() && this->getSuit() == card->getSuit();
    }
    bool match(string card){
        cout << this->face + this->suit << endl;
        cout << this->getFace() + this->getSuit() << endl;
        cout << "card : " << card << endl;
        string facesuit = this->face + this->suit;
        if (facesuit == card) cout <<  "hellow" << endl;
        return this->getFace() + this->getSuit() == card;
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


/*
 * This is discussion thread.
 * In our case to string is different depending on whether it is joker or normal card
 *
 * The case for value of each card
 * I think it is better to separate value from card because wild card has different value depending on the round
 *
 * Get face and suit are same among all the cards. So, the need to define that in child functions.
 *
 * */