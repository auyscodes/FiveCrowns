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
        this->players = players;
    }

private:

    vector<Player*> * players;
};


#endif //FIVECROWNS_DATALAYER_H
