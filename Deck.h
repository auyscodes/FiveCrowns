//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_DECK_H
#define FIVECROWNS_DECK_H



#include "CardCollection.h"
#include "Card.h"
#include "Joker.h"
#include <vector>

using namespace std;
class Deck: public CardCollection {
public:
//    void shuffle(){
//        CardCollection::shuffle();
//    }
//
//    bool isEmpty(){
//        return CardCollection::isEmpty();
//    }
    static class Builder{
    public:
        Builder numericFace(int begin, int end){
               this->begin = begin;
               this->end = end;
               return *this;
        }
        Builder specialFace(vector<string> special_face){
            this->special_face = special_face;
            return *this;
        }
        Builder suits(vector<string> _suits){
            this->_suits = _suits;
            return *this;
        }
        Builder joker(int numJokers){
            this->numJokers = numJokers;
            return *this;
        }
        Deck build(){
            Deck* deck = new Deck();
            if (_suits.empty() || (special_face.empty() && (begin==NULL || end==NULL))) throw "Deck properly not initialized";
            for (auto _suit: _suits){
                for (auto i=begin;i<=end;i++){
                    CardInterface* card = new Card();
                    card->setFace(to_string(i));
                    card->setSuit(_suit);
                    deck->addFront(card);
                }
                for (auto sp_face: special_face){
                    CardInterface* card = new Card();
                    card->setFace(sp_face);
                    card->setSuit(_suit);
                    deck->addFront(card);
                }
            }
            for (auto i=1;i<=numJokers;i++){
                CardInterface * card = new Joker();
                card->setFace(to_string(i));
                card->setSuit("J");
                deck->addFront(card);
            }
            return *deck;
        }

    private:
        int begin;
        int end;
        vector<string> special_face;
        vector<string> _suits;
        int numJokers;
    };


};


#endif //FIVECROWNS_DECK_H

/*
 * Once the deck is build no adding or removing
 *
 * */