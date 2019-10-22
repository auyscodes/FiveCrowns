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

    CardCollection* getCardCollection(){
        return CardPile::getInstance();
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
	
private:

    vector<Player*> * players;
	int nextPlayerIndex;
	int round;
	int humanPlayerIndex;
	int computerPlayerIndex;
};


#endif //FIVECROWNS_DATALAYER_H
