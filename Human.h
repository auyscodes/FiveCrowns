//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_HUMAN_H
#define FIVECROWNS_HUMAN_H


#include "Player.h"

class Human: public Player {
public:
    void play();

private:
    void askToChooseCardFromDrawPileOrDiscardPile();
    void showDrawAndDiscardPile(); // To be removed later while refactoring
    void showHand();
};


#endif //FIVECROWNS_HUMAN_H
