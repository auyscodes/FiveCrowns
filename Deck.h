//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_DECK_H
#define FIVECROWNS_DECK_H



#include "CardCollection.h"
#include "Card.h"
#include "Joker.h"
#include <vector>

/*
	Representation of Deck.
	Contains builder class that helps in building deck.

	Note: Built this way so that it will be easier if deck class might have
	some specific functions
*/
using namespace std;
class Deck: public CardCollection {
public:
	/*
		Builder class for making a check
	*/
    static class Builder{
    public:
		/*
			Takes range of numeric face
			For five crowns numeric face begins at 3 and ends at 10
			@param begin beginning of numeric face, inclusive (3 for this project)
			@param end of numeric face, inclusive (10 for this project)
			@return Object of type Deck::Builder
		*/
        Builder numericFace(int begin, int end){
               this->begin = begin;
               this->end = end;
               return *this;
        }
		/*
			Takes Jack, Queen, King etc face cards
			
			@param special_face collection of special faces
			@return Object of type Deck::Builder
		*/
        Builder specialFace(vector<string> special_face){
            this->special_face = special_face;
            return *this;
        }
		/*
			Takes Hearts, Spades, Diamonds, Tridents, etc suits
			@param _suits collection of suits
			@return Object of type Deck::Builder
		*/
        Builder suits(vector<string> _suits){
            this->_suits = _suits;
            return *this;
        }
		/*
			Number of jokers to build starting at face 1 
			@param numJokers Number of jokers 
			@return Object of type Deck::Builder
		*/
        Builder joker(int numJokers){
            this->numJokers = numJokers;
            return *this;
        }
		/*
			Builds and returns deck object
			@exception Throws exception if builder is not properly initialized
			@return Object of type deck
		*/
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
        int begin; // beginning of numeric face e.g 3 for five crowns
        int end; // end of face numeric face e.g. 10 for five crowns
        vector<string> special_face; // J,Q, K etc. faces
        vector<string> _suits; // H (hearts), D(diamonds), T(tridents) faces
        int numJokers; // number of Jokers
    };


};


#endif //FIVECROWNS_DECK_H

/*
 * Once the deck is build no adding or removing
 *
 * */