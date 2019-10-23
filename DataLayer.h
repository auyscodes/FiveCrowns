//
// Created by nbhat on 9/23/2019.
//

#ifndef FIVECROWNS_DATALAYER_H
#define FIVECROWNS_DATALAYER_H


#include "CardCollection.h"
#include "DrawPile.h"
#include "DiscardPile.h"
#include "CardPile.h"
#include "Player.h"
#include "Deck.h"

class DataLayer {
public:
	

	DataLayer(vector<Player*>* players, int nextPlayerIndex, int startRound, int humanPlayerIndex, int computerPlayerIndex) {
		this->players = players;
		this->nextPlayerIndex = nextPlayerIndex;
		this->round = startRound;
		this->humanPlayerIndex = humanPlayerIndex;
		this->computerPlayerIndex = computerPlayerIndex;
	}

    CardCollection* getDrawPile() {
        return DrawPile::getInstance();
    }

    CardCollection* getDisCardPile(){
        return DiscardPile::getInstance();
    }

    CardPile* getCardPile(){
        return CardPile::getInstance();
    }
	void setCardCollection() {
		Deck deck1 = Deck::Builder().numericFace(3, 9).specialFace({ "J", "Q", "K", "X" }).suits(
			{ "C", "H", "D", "S", "T" }).joker(3).build();
		deck1.shuffle();
		Deck deck2 = Deck::Builder().numericFace(3, 9).specialFace({ "J", "Q", "K", "X" }).suits(
			{ "C", "H", "D", "S", "T" }).joker(3).build();
		deck2.shuffle();
		CardPile* cardCollection = CardPile::getInstance();
		cardCollection->collect(&deck1);
		cardCollection->collect(&deck2);
		cardCollection->shuffle();
	}
    vector<Player*>* getPlayers(){
        return players;
    }

    void setPlayers(vector<Player*> * players){
		cout << players->size();
        this->players = players;
    }
	void setNextPlayerIndex(int index) {
		this->nextPlayerIndex = index;
	}
	int getNextPlayerIndex() {
		return nextPlayerIndex;
	}
	void setRound(int round) {
		this->round = round;
	}
	int getRound() {
		return this->round;
	}
	int getHumanPlayerIndex() {
		return this->humanPlayerIndex;
	}
	void setHumanPlayerIndex(int index) {
		this->humanPlayerIndex = index;
	}
	void setComputerPlayerIndex(int index) {
		this->computerPlayerIndex = index;
	}
	int getComputerPlayerIndex() {
		return this->computerPlayerIndex;
	}
	string getNextPlayer() {
		if (nextPlayerIndex == humanPlayerIndex) return "Human";
		if (nextPlayerIndex == computerPlayerIndex) return "Computer";
	}
	bool isLoad() {
		return this->_isLoad;
	}
	void turnIsLoadOn() {
		this->_isLoad = true;
	}
	void turnIsLoadOff() {
		this->_isLoad = false;
	}
	~DataLayer() {
		delete players;
	}
private:

    vector<Player*> * players;
	int nextPlayerIndex;
	int round;
	int humanPlayerIndex;
	int computerPlayerIndex;
	bool _isLoad = false;
};


#endif //FIVECROWNS_DATALAYER_H
