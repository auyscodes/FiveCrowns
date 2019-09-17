//
// Created by nbhat on 9/16/2019.
//

#ifndef FIVECROWNS_CARDPILE_H
#define FIVECROWNS_CARDPILE_H


#include "CardCollection.h"

class CardPile: public CardCollection {
public:
    static CardPile* getInstance();
private:
    CardPile();
    static CardPile* instance;
};


#endif //FIVECROWNS_CARDPILE_H
