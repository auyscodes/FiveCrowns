//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_ROUND_H
#define FIVECROWNS_ROUND_H


#include "Player.h"
#include "DrawPile.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "CardPile.h"
#include "UI.h"
#include "DataLayer.h"

class UI;
#include <map>

class Round: public IGoOut {
public:

    Round(int round, DataLayer* dataLayer);
    void start();
    void deal();
    int getRoundNumber(){
        return this->numCardsToDeal - 2; // in round 1 we deal 3 cards
    }
     vector<Player*> * getPlayers(); // function might not be necessary
    void collectCardsFromPiles();
    void goOut(Hand* hand);
private:
    int numCardsToDeal;
    const int startRound = 1;
    DataLayer* dataLayer;
    bool onePlayerHasGoneOut;
    void setGoOutListener();

    int getScore(Card* card);
    string convertNumCardsToDealToWildCards(int numCardsToDeal);
    bool checkGoOutPossible(CardCollection* hand);


    int countScore(CardCollection *hand);

    bool checkRun(CardCollection * hand){
        cout << "Executig checkRun function" << endl;
        vector<CardCollection*> normalAndSpecialCardsOfHands = hand->separateNormalCardsFromOthers();
        CardCollection* normalCards = normalAndSpecialCardsOfHands[0];
        CardCollection* specialCards = normalAndSpecialCardsOfHands[1];
        CardCollection* checkedSpecialCards = new CardCollection();
        // first checking suit
        if (normalCards->sameSuit()){

            int size = normalCards->getSize();
            CardInterface* prevCard = normalCards->getFront();
            CardInterface* currCard;
            int count = 1;
            while(count< size){
                currCard = normalCards->getCardAt(count);
                if (prevCard->getValue() != currCard->getValue() + 1){
                    if (specialCards->isEmpty()) return false;
                    checkedSpecialCards->addFront(specialCards->popFront());
                }
                prevCard = currCard;
                count++;
            }
            return true;
        }
        return false;
    }

    bool checkBook(CardCollection * hand){
        cout << "Executing checkBook function" << endl;
        vector<CardCollection*> normalAndSpecialCards = hand->separateNormalCardsFromOthers();
        CardCollection* normalCards = normalAndSpecialCards[0];
        CardCollection* specialCards = normalAndSpecialCards[1];
        CardCollection* checkedSpecailCards = new CardCollection();

        int size = normalCards->getSize();
        int count = 1;
        CardInterface* prevCard = normalCards->getFront();
        CardInterface* currCard;

        while(count<size){
            currCard = normalCards->getCardAt(count);
            if (prevCard->getValue() != currCard->getValue()){
                if (specialCards->isEmpty()) return false;
                checkedSpecailCards->addFront(specialCards->popFront());
            }
            prevCard = currCard;
            count++;
        }



        return true;
    }

};


#endif //FIVECROWNS_ROUND_H
