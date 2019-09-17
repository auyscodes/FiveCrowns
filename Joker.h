//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_JOKER_H
#define FIVECROWNS_JOKER_H


#include "CardInterface.h"

/*
 * Joker card has suit joker and face as 1,2 and 3 for this
 * project*/

class Joker: public CardInterface {
public:
    string toString();
    string getFace();
    string getSuit();
    void setFace(string face);
    void setSuit(string suit);

};


#endif //FIVECROWNS_JOKER_H
