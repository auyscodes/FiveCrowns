//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_PLAYER_H
#define FIVECROWNS_PLAYER_H


#include "Hand.h"
#include <iostream>
class Player {
public:
    Player();
    virtual void play() = 0;
    void setCard(CardInterface* card);
    CardCollection* getHand();
private:
    Hand* hand;
};


#endif //FIVECROWNS_PLAYER_H
